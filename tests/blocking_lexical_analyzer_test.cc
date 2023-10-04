#include <gtest/gtest.h>

#include <memory>

#include "error.h"
#include "reader/reader.h"
#include "reader/blocking_file_reader.h"
#include "reader/string_reader.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "lexical_analyzer/blocking_lexical_analyzer.h"

TEST(BlockingLexicalAnaluyzerTests, TestAllTokensFromFile) {
  const std::string test_file_content { ";" };
  std::unique_ptr<yalpconf::BlockingFileReader> reader { 
      std::make_unique<yalpconf::BlockingFileReader>("tokens.conf") };
  yalpconf::Error error_reader = reader->ReadConfiguration(); 
  ASSERT_EQ(error_reader.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_FALSE(reader->empty()); 
  yalpconf::BlockingLexicalAnalyzer lexical_analyzer(std::move(reader));
  yalpconf::Error error_lex = lexical_analyzer.ScanTokens();
  ASSERT_EQ(error_lex.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_FALSE(lexical_analyzer.empty()); 

  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorComma);
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorSemicolon);
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorOpenCurlyBracket);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::SeparatorCloseCurlyBracket, "}"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::SeparatorOpenSquareBracket, "["));
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorCloseSquareBracket);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::OperatorEquals, "="));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::DecimalInteger, "120"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::DecimalInteger, "020"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::DecimalInteger, "001"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::DecimalInteger, "000"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::HexadecimalInteger, "0x20"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::HexadecimalInteger, "0X10"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::HexadecimalInteger, "0xFa03Cb"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::BinaryInteger, "0b10"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::BinaryInteger, "0B01"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::KeywordTrue, "true"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::KeywordTrue);
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::KeywordTrue);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::KeywordTrue, "TruE"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::KeywordFalse, "false"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::KeywordFalse);
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::KeywordFalse);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::KeywordFalse, "FaLsE"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::String, "string"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::Identifier, "identifier"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::Identifier, "setting"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::Identifier, "__test"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::Identifier, "_test-2"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorOpenCurlyBracket);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::Identifier, "_close"));
  ASSERT_EQ(lexical_analyzer.TakeNextToken().type, yalpconf::TokenType::SeparatorCloseCurlyBracket);
  ASSERT_EQ(lexical_analyzer.TakeNextToken(), yalpconf::Token(yalpconf::TokenType::String, "multi\nline\nstring"));
}

TEST(BlockingLexicalAnaluyzerTests, TestEmptyFile) {
  const std::string test_file_content { ";" };
  std::unique_ptr<yalpconf::StringReader> reader { 
      std::make_unique<yalpconf::StringReader>("") };
  ASSERT_TRUE(reader->empty()); 
  yalpconf::BlockingLexicalAnalyzer lexical_analyzer(std::move(reader));
  yalpconf::Error error_lex = lexical_analyzer.ScanTokens();
  ASSERT_EQ(error_lex.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_TRUE(lexical_analyzer.empty()); 
}

void TestUnxpectedSymbol(std::string input, size_t line, std::string near_string) {
  std::unique_ptr<yalpconf::StringReader> reader { 
      std::make_unique<yalpconf::StringReader>(input) };
  ASSERT_FALSE(reader->empty()); 
  yalpconf::BlockingLexicalAnalyzer lexical_analyzer(std::move(reader));
  yalpconf::Error error_lex = lexical_analyzer.ScanTokens();
  ASSERT_EQ(error_lex.GetCode(), yalpconf::ErrorCode::UnexpectedSymbol); 
  ASSERT_EQ(error_lex.GetLine(), line); 
  ASSERT_EQ(error_lex.GetNearString(), near_string); 
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidSymbol) {
  TestUnxpectedSymbol("{ \n [ \n }/*\n*/-test_ } ]", 4, "-");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidBinaryInteger) {
  TestUnxpectedSymbol("0bz", 1, "0b");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidHexadecimalInteger) {
  TestUnxpectedSymbol("0xz", 1, "0x");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidCStyleOneLineComment) {
  TestUnxpectedSymbol("/test", 1, "t");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidCStyleMultiLineComment1) {
  TestUnxpectedSymbol("/*1\n2\n3**", 3, "**");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidCStyleMultiLineComment2) {
  TestUnxpectedSymbol("/*1\n2\n3end", 3, "nd");
}

TEST(BlockingLexicalAnaluyzerTests, TestInvalidString) {
  TestUnxpectedSymbol("\"test", 1, "t");
}
