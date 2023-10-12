#include <gtest/gtest.h>

#include <memory>

#include "error.h"
#include "reader/reader.h"
#include "reader/blocking_file_reader.h"
#include "lexical_analyzer/token.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "lexical_analyzer/blocking_lexical_analyzer.h"
#include "parser/parser.h"
#include "parser/lr0_parser.h"
#include "types/int.h"
#include "types/boolean.h"
#include "types/string.h"
#include "types/array.h"
#include "types/object.h"
#include "types/value.h"

TEST(LR0ParserTests, TestParse) {
  std::unique_ptr<yalpconf::BlockingFileReader> reader { 
      std::make_unique<yalpconf::BlockingFileReader>("parser_test.conf") };
  reader->ReadConfiguration();
  ASSERT_FALSE(reader->empty()); 
  std::unique_ptr<yalpconf::BlockingLexicalAnalyzer> lexical_analyzer {
    std::make_unique<yalpconf::BlockingLexicalAnalyzer>(std::move(reader)) };
  yalpconf::Error error_lex = lexical_analyzer->ScanTokens();
  ASSERT_EQ(error_lex.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_FALSE(lexical_analyzer->empty()); 

  yalpconf::Lr0Parser parser(std::move(lexical_analyzer));
  yalpconf::Error error { parser.ParseTokens() };
  ASSERT_EQ(error.GetCode(), yalpconf::ErrorCode::None) << error.GetMessage();

  auto root = parser.GetRootObject();

  ASSERT_TRUE(root->exist("str"));
  ASSERT_TRUE(root->value("str")->Is<yalpconf::String>());
  ASSERT_EQ(root->value("str")->As<yalpconf::String>().value(), "string");

  ASSERT_TRUE(root->exist("set"));
  ASSERT_TRUE(root->value("set")->Is<yalpconf::Boolean>());
  ASSERT_EQ(root->value("set")->As<yalpconf::Boolean>().value(), true);

  ASSERT_TRUE(root->exist("set_1"));
  ASSERT_TRUE(root->value("set_1")->Is<yalpconf::Int>());
  ASSERT_EQ(root->value("set_1")->As<yalpconf::Int>().value(), 1234);

  ASSERT_TRUE(root->exist("set-2"));
  ASSERT_TRUE(root->value("set-2")->Is<yalpconf::Int>());
  ASSERT_EQ(root->value("set-2")->As<yalpconf::Int>().value(), 255);

  ASSERT_TRUE(root->exist("_"));
  ASSERT_TRUE(root->value("_")->Is<yalpconf::Int>());
  ASSERT_EQ(root->value("_")->As<yalpconf::Int>().value(), 13);

  ASSERT_TRUE(root->exist("array"));
  ASSERT_TRUE(root->value("array")->Is<yalpconf::Array>());
  auto array { root->value("array")->As<yalpconf::Array>() };
  ASSERT_EQ(array.size(), 3);
  ASSERT_TRUE(array[0]->Is<yalpconf::Int>());
  ASSERT_EQ(array[0]->As<yalpconf::Int>().value(), 1);
  ASSERT_TRUE(array[1]->Is<yalpconf::Int>());
  ASSERT_EQ(array[1]->As<yalpconf::Int>().value(), 2);
  ASSERT_TRUE(array[2]->Is<yalpconf::Int>());
  ASSERT_EQ(array[2]->As<yalpconf::Int>().value(), 3);

  ASSERT_TRUE(root->exist("object"));
  ASSERT_TRUE(root->value("object")->Is<yalpconf::Object>());
  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().exist("obj1"));
  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().value("obj1")->Is<yalpconf::String>());
  ASSERT_EQ(root->value("object")->As<yalpconf::Object>().value("obj1")->As<yalpconf::String>().value(), "obj");

  ASSERT_TRUE(root->exist("object"));
  ASSERT_TRUE(root->value("object")->Is<yalpconf::Object>());
  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().exist("obj2"));
  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().value("obj2")->Is<yalpconf::String>());
  ASSERT_EQ(root->value("object")->As<yalpconf::Object>().value("obj2")->As<yalpconf::String>().value(), "obj");

  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().exist("objein"));
  ASSERT_TRUE(root->value("object")->As<yalpconf::Object>().value("objein")->Is<yalpconf::Object>());
  auto objein { root->value("object")->As<yalpconf::Object>().value("objein")->As<yalpconf::Object>() };
  ASSERT_TRUE(objein.exist("arr"));
  ASSERT_TRUE(objein.value("arr")->Is<yalpconf::Array>());
  auto arr { objein.value("arr")->As<yalpconf::Array>() };
  ASSERT_EQ(arr.size(), 5);
  ASSERT_TRUE(arr[0]->Is<yalpconf::String>());
  ASSERT_EQ(arr[0]->As<yalpconf::String>().value(), "str1");
  ASSERT_TRUE(arr[1]->Is<yalpconf::String>());
  ASSERT_EQ(arr[1]->As<yalpconf::String>().value(), "str2");
  ASSERT_TRUE(arr[2]->Is<yalpconf::Int>());
  ASSERT_EQ(arr[2]->As<yalpconf::Int>().value(), 1);
  ASSERT_TRUE(arr[3]->Is<yalpconf::Int>());
  ASSERT_EQ(arr[3]->As<yalpconf::Int>().value(), 2);
  ASSERT_TRUE(arr[4]->Is<yalpconf::Boolean>());
  ASSERT_EQ(arr[4]->As<yalpconf::Boolean>().value(), false);
}
