#ifndef YALPCONF_INCLUDE_TYPES_STRING_H_
#define YALPCONF_INCLUDE_TYPES_STRING_H_

#include "types/value.h"

namespace yalpconf {

class String : public Value {
  public:
    explicit String(const std::string& value) : value_ { value } {}
    std::string value() const { return value_; }
  private:
    std::string value_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_STRING_H_
