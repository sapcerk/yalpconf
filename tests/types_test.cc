#include <gtest/gtest.h>

#include <memory>

#include "types/value.h"
#include "types/int.h"
#include "types/boolean.h"
#include "types/string.h"
#include "types/array.h"
#include "types/object.h"
#include "lexical_analyzer/token.h"

TEST(TypesTests, TestIntDecimal) {
  yalpconf::Int val(yalpconf::Token(yalpconf::TokenType::DecimalInteger, "101"));
  ASSERT_EQ(val.value(), 101);
}

TEST(TypesTests, TestIntHexadecimal) {
  yalpconf::Int val(yalpconf::Token(yalpconf::TokenType::HexadecimalInteger, "0x65"));
  ASSERT_EQ(val.value(), 101);
}

TEST(TypesTests, TestIntBinaryDecimal) {
  yalpconf::Int val(yalpconf::Token(yalpconf::TokenType::BinaryInteger, "0B101"));
  ASSERT_EQ(val.value(), 5);
}

TEST(TypesTests, TestBooleanTrue) {
  yalpconf::Boolean val(yalpconf::TokenType::KeywordTrue);
  ASSERT_EQ(val.value(), true);
}

TEST(TypesTests, TestBooleanFalse) {
  yalpconf::Boolean val(yalpconf::TokenType::KeywordFalse);
  ASSERT_EQ(val.value(), false);
}

TEST(TypesTests, TestString) {
  yalpconf::String val("string 101");
  ASSERT_EQ(val.value(), "string 101");
}

TEST(TypesTests, TestArraySameVlaues) {
  yalpconf::Array arr;
  std::shared_ptr<yalpconf::Value> value;
  value = std::make_shared<yalpconf::Int>(yalpconf::Token(yalpconf::TokenType::DecimalInteger, "101"));
  arr.add(std::move(value));
  value.reset();
  value = std::make_shared<yalpconf::Int>(yalpconf::Token(yalpconf::TokenType::HexadecimalInteger, "0xFF"));
  arr.add(std::move(value));
  value.reset();
  value = std::make_shared<yalpconf::Int>(yalpconf::Token(yalpconf::TokenType::BinaryInteger, "0B101"));
  arr.add(std::move(value));
  value.reset();
  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0]->As<yalpconf::Int>().value(), 101);
  ASSERT_EQ(arr[1]->As<yalpconf::Int>().value(), 255);
  ASSERT_EQ(arr[2]->As<yalpconf::Int>().value(), 5);
}

TEST(TypesTests, TestArrayMixedValues) {
  yalpconf::Array arr;
  std::shared_ptr<yalpconf::Value> value;
  value = std::make_shared<yalpconf::Int>(yalpconf::Token(yalpconf::TokenType::DecimalInteger, "101"));
  arr.add(std::move(value));
  value = std::make_shared<yalpconf::Boolean>(yalpconf::TokenType::KeywordTrue);
  arr.add(std::move(value));
  value = std::make_shared<yalpconf::String>("string 101");
  arr.add(std::move(value));
  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0]->As<yalpconf::Int>().value(), 101);
  ASSERT_EQ(arr[1]->As<yalpconf::Boolean>().value(), true);
  ASSERT_EQ(arr[2]->As<yalpconf::String>().value(), "string 101");
}

TEST(TypesTests, TestObjectValue) {
  std::shared_ptr<yalpconf::Object> obj { std::make_shared<yalpconf::Object>() };
  ASSERT_EQ(obj->exist("set1"), false);
  std::shared_ptr<yalpconf::Value> value;
  value = std::make_shared<yalpconf::Int>(yalpconf::Token(yalpconf::TokenType::DecimalInteger, "101"));
  obj->add("set1", std::move(value));
  ASSERT_EQ(obj->exist("set2"), false);
  ASSERT_EQ(obj->exist("set1"), true);
  value = std::make_shared<yalpconf::String>("string 101");
  obj->add("set2", std::move(value));
  ASSERT_EQ(obj->exist("set1"), true);
  ASSERT_EQ(obj->value("set1")->As<yalpconf::Int>().value(), 101);
  ASSERT_EQ(obj->exist("set2"), true);
  ASSERT_EQ(obj->value("set2")->As<yalpconf::String>().value(), "string 101");
}
