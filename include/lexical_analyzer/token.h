#ifndef YALPCONF_INCLUDE_LEXICAL_ANALYZER_TOKEN_H_
#define YALPCONF_INCLUDE_LEXICAL_ANALYZER_TOKEN_H_

#include <string>
#include <vector>

namespace yalpconf {

enum class TokenType : int {
  Empty,
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
  size_t line;

  explicit Token() 
      : type { TokenType::Empty } {}

  explicit Token(TokenType type) 
      : type { type } {}

  explicit Token(TokenType type, const std::string& value) 
      : type { type }, value { value }, line { 0 } {}

  explicit Token(TokenType type, const std::string& value, size_t line) 
      : type { type }, value { value }, line { line } {}

  Token(TokenType type, std::string&& value) noexcept
      : type { type }, value { std::move(value) }, line { 0 } {}

  Token(TokenType type, std::string&& value, size_t line) noexcept
      : type { type }, value { std::move(value) }, line { line } {}
};

inline bool operator==(const yalpconf::Token& lhs, const yalpconf::Token& rhs) {
  return (lhs.type == rhs.type && lhs.value == rhs.value);
}

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_LEXICAL_ANALYZER_TOKEN_H_
