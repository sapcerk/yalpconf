#ifndef YALPCONF_SRC_LEXICAL_ANALYZER_PATTERNS_H_
#define YALPCONF_SRC_LEXICAL_ANALYZER_PATTERNS_H_

#include <cctype>

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "lexical_analyzer/token.h"

namespace yalpconf {

inline const std::unordered_set<std::string> kKeywordAnyCase__ {
  "false", "true",
};

inline const std::unordered_map<std::string, TokenType> kKeywords__ {
  { "false", TokenType::KeywordFalse }, { "true", TokenType::KeywordTrue },
};

inline std::string TokenToLower(std::string token) {
  std::transform(token.begin(), token.end(), token.begin(),
      [](unsigned char symbol) { return std::tolower(symbol); });
  return token;
}

inline void TokenToLowerEmplace(std::string& token) {
  std::transform(token.begin(), token.end(), token.begin(),
      [](unsigned char symbol) { return std::tolower(symbol); });
}

inline bool IsSpacer(char symbol) {
  switch (symbol) {
    case ' ':
    case '\n':
    case '\t':
    case '\r':
      return true;
    default:
      return false;
  }
}

inline bool IsStringSeparator(char symbol) {
  return (symbol == '"');
}

inline bool IsOperatorEquals(char symbol) {
  return (symbol == '=');
}

inline bool IsSeparatorComma(char symbol) {
  return (symbol == ',');
}

inline bool IsSeparatorSemicolon(char symbol) {
  return (symbol == ';');
}

inline bool IsSeparatorOpenCurlyBracket(char symbol) {
  return (symbol == '{');
}

inline bool IsSeparatorCloseCurlyBracket(char symbol) {
  return (symbol == '}');
}

inline bool IsSeparatorOpenSquareBracket(char symbol) {
  return (symbol == '[');
}

inline bool IsSeparatorCloseSquareBracket(char symbol) {
  return (symbol == ']');
}

inline bool IsPythonComment(char symbol) {
  return (symbol == '#');
}

inline bool IsCComment(char symbol) {
  return (symbol == '/');
}

inline bool IsCMultilineComment(char symbol) {
  return (symbol == '*');
}

inline bool IsIntegerBaseSelect(char symbol) {
  return (symbol == '0');
}

inline bool IsHexadecimalIntegerBase(char symbol) {
  return (symbol == 'x' || symbol == 'X');
}

inline bool IsBinaryIntegerBase(char symbol) {
  return (symbol == 'b' || symbol == 'B');
}

inline bool IsDecimalInteger(char symbol) {
  return (symbol >= '0' && symbol <= '9');
}

inline bool IsHexadecimalInteger(char symbol) {
  return ((symbol >= '0' && symbol <= '9') ||
          (symbol >= 'a' && symbol <= 'f') ||
          (symbol >= 'A' && symbol <= 'F'));
}

inline bool IsBinaryInteger(char symbol) {
  return (symbol == '0' || symbol == '1');
}

inline bool IsIdentifierKeywordStartsWith(char symbol) {
  return (symbol == '_' ||
          (symbol >= 'a' && symbol <= 'z') ||
          (symbol >= 'A' && symbol <= 'Z'));
}

inline bool IsIdentifierKeywordBody(char symbol) {
  return (symbol == '-' || symbol == '_' ||
          (symbol >= '0' && symbol <= '9') ||
          (symbol >= 'a' && symbol <= 'z') ||
          (symbol >= 'A' && symbol <= 'Z'));
}

inline bool IsKeywordAnyCase(const std::string& token) {
  return kKeywordAnyCase__.count(token) != 0;
}

inline TokenType GetKeywordTokenType(const std::string& token) {
  return kKeywords__.at(token);
}

} // namespace yalpconf

#endif // YALPCONF_SRC_LEXICAL_ANALYZER_PATTERNS_H_
