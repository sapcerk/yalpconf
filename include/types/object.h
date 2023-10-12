#ifndef YALPCONF_INCLUDE_TYPES_OBJECT_H_
#define YALPCONF_INCLUDE_TYPES_OBJECT_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "types/value.h"

namespace yalpconf {

class Object : public Value {
  public:
    Object() = default;
    void add(std::string&& setting_name, std::shared_ptr<Value>&& value) { 
      value_.emplace(std::make_pair( std::move(setting_name), std::move(value))); 
    }
    void add(const std::string& setting_name, std::shared_ptr<Value> value) { 
      value_.insert({setting_name, value}); 
    }
    bool exist(std::string setting_name) const {
      return value_.contains(setting_name);
    }
    std::shared_ptr<Value> value(std::string setting_name) const { return value_.at(setting_name); }
  private:
    std::unordered_map<std::string, std::shared_ptr<Value>> value_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_OBJECT_H_
