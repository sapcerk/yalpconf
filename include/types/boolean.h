#ifndef YALPCONF_INCLUDE_TYPES_BOOLEAN_H_
#define YALPCONF_INCLUDE_TYPES_BOOLEAN_H_

#include "types/value.h"
#include "lexical_analyzer/token.h"

namespace yalpconf {

class Boolean : public Value {
  public:
    explicit Boolean(TokenType token_type) {
      value_ = (token_type == TokenType::KeywordTrue);
    }
    bool value() const { return value_; }
  private:
    bool value_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_BOOLEAN_H_
