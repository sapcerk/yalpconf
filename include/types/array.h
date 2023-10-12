#ifndef YALPCONF_INCLUDE_TYPES_ARRAY_H_
#define YALPCONF_INCLUDE_TYPES_ARRAY_H_

#include <vector>
#include <memory>

#include "types/value.h"

namespace yalpconf {

class Array : public Value {
  public:
    Array() = default;
    void add(std::shared_ptr<Value>&& value) { 
      value_.emplace_back(std::move(value)); 
    }
    size_t size() {
      return value_.size();
    }
    std::shared_ptr<Value> operator[] (size_t i) {
      return value_[i];
    } 
  private:
    std::vector<std::shared_ptr<Value>> value_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_ARRAY_H_
