#ifndef REDIS_H
#define REDIS_H

#include <hiredis/hiredis.h>
#include <thread>
#include <functional>

// redis发布订阅相关功能的封装类
class Redis {
public:
    Redis();
    ~Redis();

    // 连接redis server
    bool Connect();

    // 发布消息
    bool Publish(int channel, std::string message);

    // 订阅消息
    bool Subscribe(int channel);

    // 取消订阅消息
    bool Unsubscribe(int channel);

    // 接收通道的消息，单独的线程负责接收
    void ObserverChannelMessage();

    // 初始化回调，该回调用于通知消息
    void InitNotifyHandler(std::function<void(int, std::string)> callback);

private:
    // hiredis同步上下文对象，负责publish消息
    redisContext *publish_context_;

    // hiredis同步上下文对象，负责subscribe消息
    redisContext *subcribe_context_;

    // 回调操作，将订阅频道中的消息向业务层通知
    std::function<void(int, std::string)> notify_message_handler_;
};

#endif