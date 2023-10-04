#include <iostream>
#include <string>
#include <vector>

#include "error.h"
#include "reader/reader.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "lexical_analyzer/blocking_lexical_analyzer.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/patterns.h"

namespace yalpconf {

BlockingLexicalAnalyzer::BlockingLexicalAnalyzer(std::unique_ptr<const Reader> reader)
    : LexicalAnalyzer(std::move(reader)), line_ { 1 }, 
      next_token_position_ { 0 } {};

void BlockingLexicalAnalyzer::AddToken(TokenType token_type) {
    tokens_.emplace_back(Token(token_type, std::move(current_token_)));
    current_token_.clear();
}

void BlockingLexicalAnalyzer::AddSymbolToCurrentToken(char symbol) {
  current_token_.push_back(symbol);
}

char BlockingLexicalAnalyzer::ReaderTakeNextSymbol() {
  char symbol = reader_->TakeNextSymbol();
  if (symbol == '\n')
    ++line_;
  return symbol;
}

Error BlockingLexicalAnalyzer::AddString() {
  char symbol;
  while (!reader_->empty() && !IsStringSeparator(symbol = ReaderTakeNextSymbol())) {
    AddSymbolToCurrentToken(symbol);
  }
  if (!IsStringSeparator(symbol))
    return Error(ErrorCode::UnexpectedSymbol, line_, symbol);
  AddToken(TokenType::String);
  return Error(ErrorCode::None);
}

void BlockingLexicalAnalyzer::AddPythonComment() {
  while (!reader_->empty() && ReaderTakeNextSymbol() != '\n') {}
}

Error BlockingLexicalAnalyzer::AddCComment() {
  char symbol { ReaderTakeNextSymbol() };
  if (IsCComment(symbol)) {
    while (!reader_->empty() && ReaderTakeNextSymbol() != '\n') {}
  } else if (IsCMultilineComment(symbol)) {
    char prev_symbol = '\0';
    symbol = '\0';
    while (!reader_->empty() && 
        !(IsCMultilineComment(prev_symbol) && IsCComment(symbol))) {
      prev_symbol = symbol;
      symbol = ReaderTakeNextSymbol();
    }
    if (!(IsCMultilineComment(prev_symbol) && IsCComment(symbol)))
      return Error(ErrorCode::UnexpectedSymbol, line_, 
          std::string{prev_symbol, symbol});
  } else {
    return Error(ErrorCode::UnexpectedSymbol, line_, symbol);
  }
  return Error(ErrorCode::None);
}

Error BlockingLexicalAnalyzer::IntegerBaseSelect() {
  if (reader_->empty())
    return AddDecimalInteger();
  char symbol { reader_->CheckNextSymbol() };
  if (IsHexadecimalIntegerBase(symbol)) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
    return AddHexadecimalInteger();
  } else if (IsBinaryIntegerBase(symbol)) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
    return AddBinaryInteger();
  }
  return AddDecimalInteger();
}

Error BlockingLexicalAnalyzer::AddHexadecimalInteger() {
  if (!reader_->empty() && IsHexadecimalInteger(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  } else {
    return Error(ErrorCode::UnexpectedSymbol, line_, current_token_);
  }
  while (!reader_->empty() && IsHexadecimalInteger(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  }
  AddToken(TokenType::HexadecimalInteger);
  return Error(ErrorCode::None);
}

Error BlockingLexicalAnalyzer::AddBinaryInteger() {
  if (!reader_->empty() && IsBinaryInteger(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  } else {
    return Error(ErrorCode::UnexpectedSymbol, line_, current_token_);
  }
  while (!reader_->empty() && IsBinaryInteger(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  }
  AddToken(TokenType::BinaryInteger);
  return Error(ErrorCode::None);
}

Error BlockingLexicalAnalyzer::AddDecimalInteger() {
  while (!reader_->empty() && IsDecimalInteger(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  }
  AddToken(TokenType::DecimalInteger);
  return Error(ErrorCode::None);
}

void BlockingLexicalAnalyzer::AddIdentifierKeyword() {
  while (!reader_->empty() && IsIdentifierKeywordBody(reader_->CheckNextSymbol())) {
    AddSymbolToCurrentToken(ReaderTakeNextSymbol());
  }
  std::string lower_token = TokenToLower(current_token_);
  if (IsKeywordAnyCase(lower_token)) {
    AddToken(GetKeywordTokenType(lower_token));
  } else {
    AddToken(TokenType::Identifier);
  }
}

Error BlockingLexicalAnalyzer::ScanTokens() {
  char symbol;
  Error error;
  while (!reader_->empty()) {
    symbol = ReaderTakeNextSymbol();
    if (IsSpacer(symbol)) {
      // nop
    } else if (IsSeparatorComma(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorComma);
    } else if (IsSeparatorSemicolon(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorSemicolon);
    } else if (IsSeparatorOpenCurlyBracket(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorOpenCurlyBracket);
    } else if (IsSeparatorCloseCurlyBracket(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorCloseCurlyBracket);
    } else if (IsSeparatorOpenSquareBracket(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorOpenSquareBracket);
    } else if (IsSeparatorCloseSquareBracket(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::SeparatorCloseSquareBracket);
    } else if (IsOperatorEquals(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddToken(TokenType::OperatorEquals);
    } else if (IsStringSeparator(symbol)) {
      error = AddString();
    } else if (IsPythonComment(symbol)) {
      AddPythonComment();
    } else if (IsCComment(symbol)) {
      error = AddCComment();
    } else if (IsIntegerBaseSelect(symbol)) {
      AddSymbolToCurrentToken(symbol);
      error = IntegerBaseSelect();
    } else if (IsDecimalInteger(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddDecimalInteger();
    } else if (IsIdentifierKeywordStartsWith(symbol)) {
      AddSymbolToCurrentToken(symbol);
      AddIdentifierKeyword();
    } else {
      return Error(ErrorCode::UnexpectedSymbol, line_, symbol);
    }
    if (error.GetCode() != ErrorCode::None)
      return error;
  }
  return Error(ErrorCode::None);
}

bool BlockingLexicalAnalyzer::empty() const {
  return next_token_position_ >= tokens_.size();
}

Token BlockingLexicalAnalyzer::CheckNextToken() const {
  return tokens_[next_token_position_];
}

Token BlockingLexicalAnalyzer::TakeNextToken() const {
  return tokens_[next_token_position_++];
}

} // namespace yalpconf
