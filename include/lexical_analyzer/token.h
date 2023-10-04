#ifndef YALPCONF_SRC_LEXICAL_ANALYZER_TOKEN_H_
#define YALPCONF_SRC_LEXICAL_ANALYZER_TOKEN_H_

#include <string>
#include <vector>

namespace yalpconf {

enum class TokenType : int {
  DecimalInteger,
  BinaryInteger,
  HexadecimalInteger,
  String,
  Identifier,
  SeparatorComma,
  SeparatorSemicolon,
  SeparatorOpenCurlyBracket,
  SeparatorCloseCurlyBracket,
  SeparatorOpenSquareBracket,
  SeparatorCloseSquareBracket,
  OperatorEquals,
  KeywordTrue,
  KeywordFalse,
};

struct Token {
  TokenType type;
  std::string value;

  explicit Token(TokenType type) 
      : type { type } {}

  explicit Token(TokenType type, const std::string& value) 
      : type { type }, value { value } {}

  Token(TokenType type, std::string&& value) noexcept
      : type { type }, value { std::move(value) } {}
};

inline bool operator==(const yalpconf::Token& lhs, const yalpconf::Token& rhs) {
  return (lhs.type == rhs.type && lhs.value == rhs.value);
}

} // namespace yalpconf

#endif // YALPCONF_SRC_LEXICAL_ANALYZER_TOKEN_H_
