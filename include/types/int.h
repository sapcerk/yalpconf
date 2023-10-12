#ifndef YALPCONF_INCLUDE_TYPES_INT_H_
#define YALPCONF_INCLUDE_TYPES_INT_H_

#include <string>

#include "types/value.h"
#include "lexical_analyzer/token.h"

namespace yalpconf {

class Int : public Value {
  public:
    explicit Int(const Token& token) {
      if (token.type == TokenType::HexadecimalInteger) {
        value_ = std::stoi(token.value.substr(2), nullptr, 16);
      } else if (token.type == TokenType::BinaryInteger) {
        value_ = std::stoi(token.value.substr(2), nullptr, 2);
      } else {
        value_ = std::stoi(token.value, nullptr, 10);
      }
    }
    const int& value() const { return value_; }
  private:
    int value_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_INT_H_
