#ifndef USER_H
#define USER_H

#include <string>

// user表的orm类
class User {
public:
    // id为-1时表示表中无该用户，状态默认为offline下线模式
    User(int id = -1, const std::string& name = "", 
            const std::string& password = "", const std::string& state = "offline")
        : id_(id)
        , name_(name)
        , password_(password)
        , state_(state) {}

    void SetId(int id) { id_ = id; }
    void SetName(const std::string& name) { name_ = name; }
    void SetPassword(const std::string& password) { password_ = password; }
    void SetState(const std::string& state) { state_ = state; }

    int GetId() const { return id_; }
    std::string GetName() const { return name_; }
    std::string GetPassword() const { return password_; }
    std::string GetState() const { return state_; }
protected:
    int id_;
    std::string name_;
    std::string password_;
    std::string state_;  // 只有online和offline两个取值
};

#endif