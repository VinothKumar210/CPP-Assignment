#pragma once

#include <string>

namespace hotel {

class Guest {
private:
    std::string id_;
    std::string name_;
    std::string phone_;
    std::string email_;

public:
  
    Guest(std::string id, std::string name, std::string phone, std::string email)
        : id_(id), 
          name_(name), 
          phone_(phone), 
          email_(email) {}


    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const std::string& getPhone() const { return phone_; }
    const std::string& getEmail() const { return email_; }

    std::string toString() const {
        return "Guest[" + id_ + "] " + name_ + " (" + email_ + ")";
    }
};

} 
