#include "redis.h"
#include <iostream>
#include <memory>
#include <functional>

// redis的ip和port
static const std::string kIp = "127.0.0.1";
static const int kPort = 6379;

Redis::Redis()
    : publish_context_(nullptr)
    , subcribe_context_(nullptr) {}

Redis::~Redis() {
    if (publish_context_) {
        redisFree(publish_context_);
    }

    if (subcribe_context_) {
        redisFree(subcribe_context_);
    }
}

bool Redis::Connect() {
    publish_context_ = redisConnect(kIp.c_str(), kPort);
    if (!publish_context_) {
        std::cerr << "Cannot connect redis" << std::endl;
        return false;
    }
    subcribe_context_ = redisConnect(kIp.c_str(), kPort);
    if (!subcribe_context_)
    {
        std::cerr << "Cannot onnect redis" << std::endl;
        return false;
    }

    // 开启单独线程，用于监听通道的消息
    std::thread observer([&]() {
        ObserverChannelMessage();
    });
    observer.detach();

    std::cout << "Connect redis-server success!" << std::endl;

    return true;
}

bool Redis::Publish(int channel, std::string message) {
    std::unique_ptr<redisReply, std::function<void(redisReply*)>> reply_ptr(
        (redisReply*)redisCommand(publish_context_, "PUBLISH %d %s", channel, message.c_str()),
        [](redisReply* redis_reply) { freeReplyObject(redis_reply); }
    );
    if (!reply_ptr) {
        std::cerr << "publish command failed!" << std::endl;
        return false;
    }
    return true;
}

// subscribe命令会造成阻塞，为了防止线程被阻塞住，所以这里不能直接调用redisCommand，
// 此方法只是订阅通道，不负责接受消息
bool Redis::Subscribe(int channel) {
    if (REDIS_ERR == redisAppendCommand(this->subcribe_context_, "SUBSCRIBE %d", channel)) {
        std::cerr << "subscribe command failed!" << std::endl;
        return false;
    }
    // 缓冲区数据发送完毕时，done会被置为1
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->subcribe_context_, &done)) {
            std::cerr << "subscribe command failed!" << std::endl;
            return false;
        }
    }
    return true;
}

// 取消订阅和订阅方法同理
bool Redis::Unsubscribe(int channel) {
    if (REDIS_ERR == redisAppendCommand(this->subcribe_context_, "UNSUBSCRIBE %d", channel)) {
        std::cerr << "unsubscribe command failed!" << std::endl;
        return false;
    }
    int done = 0;
    while (!done) {
        if (REDIS_ERR == redisBufferWrite(this->subcribe_context_, &done)) {
            std::cerr << "unsubscribe command failed!" << std::endl;
            return false;
        }
    }
    return true;
}

// 在独立线程中接收订阅通道中的消息
void Redis::ObserverChannelMessage() {
    redisReply *reply = nullptr;
    while (REDIS_OK == redisGetReply(this->subcribe_context_, (void **)&reply)) {
        if (reply != nullptr && reply->element[2] != nullptr && reply->element[2]->str != nullptr) {
            // 给业务层上报通道上发生的消息
            notify_message_handler_(atoi(reply->element[1]->str) , reply->element[2]->str);
        }

        freeReplyObject(reply);
    }
}

void Redis::InitNotifyHandler(std::function<void(int, std::string)> callback)
{
    this->notify_message_handler_ = callback;
}