#ifndef OFFLINE_MSG_MODEL_H
#define OFFLINE_MSG_MODEL_H

#include <vector>
#include <string>

class OfflineMsgModel {
public:
    // 插入
    bool Insert(int id, const std::string& msg);

    // 删除
    bool Erase(int id);

    // 查询
    std::vector<std::string> Query(int id);
};

#endif