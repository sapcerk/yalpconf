#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "error.h"

TEST(ErrorTests, TestConstructors) {
  const yalpconf::ErrorCode error_code1 = yalpconf::ErrorCode::None;
  yalpconf::Error error1 = yalpconf::Error();
  ASSERT_EQ(error1.GetCode(), error_code1);
  ASSERT_EQ(error1.GetLine(), 0);
  ASSERT_EQ(error1.GetNearString(), "");

  const yalpconf::ErrorCode error_code2 = yalpconf::ErrorCode::CantOpenFile;
  yalpconf::Error error2 = yalpconf::Error(error_code2);
  ASSERT_EQ(error2.GetCode(), error_code2);
  ASSERT_EQ(error2.GetLine(), 0);
  ASSERT_EQ(error2.GetNearString(), "");

  const yalpconf::ErrorCode error_code3 = yalpconf::ErrorCode::UnexpectedSymbol;
  const size_t line_number3 = 100;
  yalpconf::Error error3 = yalpconf::Error(error_code3, line_number3);
  ASSERT_EQ(error3.GetCode(), error_code3);
  ASSERT_EQ(error3.GetLine(), line_number3);
  ASSERT_EQ(error3.GetNearString(), "");

  const yalpconf::ErrorCode error_code4 = yalpconf::ErrorCode::UnexpectedSymbol;
  const size_t line_number4 = 100;
  const std::string near_string4 { "test" };
  yalpconf::Error error4 = yalpconf::Error(error_code4, line_number4, near_string4);
  ASSERT_EQ(error4.GetCode(), error_code4);
  ASSERT_EQ(error4.GetLine(), line_number4);
  ASSERT_EQ(error4.GetNearString(), near_string4);

  const yalpconf::ErrorCode error_code5 = yalpconf::ErrorCode::UnexpectedSymbol;
  const size_t line_number5 = 100;
  const char near_string_c5 { 't' };
  const std::string near_string5 { "t" };
  yalpconf::Error error5 = yalpconf::Error(error_code5, line_number5, near_string_c5);
  ASSERT_EQ(error5.GetCode(), error_code5);
  ASSERT_EQ(error5.GetLine(), line_number5);
  ASSERT_EQ(error5.GetNearString(), near_string5);
}

TEST(ErrorTests, TestCopyMove) {
  const yalpconf::ErrorCode error_code_none = yalpconf::ErrorCode::None;
  const size_t line_number_none = 0;
  const std::string near_string_none;
  const yalpconf::ErrorCode error_code = yalpconf::ErrorCode::UnexpectedSymbol;
  const size_t line_number = 100;
  const std::string near_string { "test" };
  yalpconf::Error error = yalpconf::Error(error_code, line_number, near_string);
  ASSERT_EQ(error.GetCode(), error_code);
  ASSERT_EQ(error.GetLine(), line_number);
  ASSERT_EQ(error.GetNearString(), near_string);
  // copy constructor
  yalpconf::Error error_cc(error);
  ASSERT_EQ(error.GetCode(), error_code);
  ASSERT_EQ(error.GetLine(), line_number);
  ASSERT_EQ(error.GetNearString(), near_string);
  ASSERT_EQ(error_cc.GetCode(), error_code);
  ASSERT_EQ(error_cc.GetLine(), line_number);
  ASSERT_EQ(error_cc.GetNearString(), near_string);
  // copy assigment
  yalpconf::Error error_ca;
  ASSERT_EQ(error_ca.GetCode(), error_code_none);
  ASSERT_EQ(error_ca.GetLine(), line_number_none);
  ASSERT_EQ(error_ca.GetNearString(), near_string_none);
  error_ca = error_cc;
  ASSERT_EQ(error_cc.GetCode(), error_code);
  ASSERT_EQ(error_cc.GetLine(), line_number);
  ASSERT_EQ(error_cc.GetNearString(), near_string);
  ASSERT_EQ(error_ca.GetCode(), error_code);
  ASSERT_EQ(error_ca.GetLine(), line_number);
  ASSERT_EQ(error_ca.GetNearString(), near_string);
  // move constructor
  yalpconf::Error error_mc(std::move(error));
  ASSERT_EQ(error.GetCode(), error_code_none);
  ASSERT_EQ(error.GetLine(), line_number_none);
  ASSERT_EQ(error.GetNearString(), near_string_none);
  ASSERT_EQ(error_mc.GetCode(), error_code);
  ASSERT_EQ(error_mc.GetLine(), line_number);
  ASSERT_EQ(error_mc.GetNearString(), near_string);
  // move assigment
  yalpconf::Error error_ma;
  ASSERT_EQ(error_ma.GetCode(), error_code_none);
  ASSERT_EQ(error_ma.GetLine(), line_number_none);
  ASSERT_EQ(error_ma.GetNearString(), near_string_none);
  error_ma = std::move(error_mc);
  ASSERT_EQ(error_mc.GetCode(), error_code_none);
  ASSERT_EQ(error_mc.GetLine(), line_number_none);
  ASSERT_EQ(error_mc.GetNearString(), near_string_none);
  ASSERT_EQ(error_ma.GetCode(), error_code);
  ASSERT_EQ(error_ma.GetLine(), line_number);
  ASSERT_EQ(error_ma.GetNearString(), near_string);
}

TEST(ErrorTests, TestMethods) {
  const yalpconf::ErrorCode error_code = yalpconf::ErrorCode::UnexpectedSymbol;
  const auto error_int = 
      static_cast<std::underlying_type_t<yalpconf::ErrorCode>>(error_code);
  const size_t line_number = 100;
  const std::string near_string { "test" };
  yalpconf::Error error = yalpconf::Error(error_code, line_number, near_string);
  ASSERT_EQ(error.GetCode(), error_code);
  ASSERT_EQ(error.GetCodeInt(), error_int);
  ASSERT_EQ(error.GetLine(), line_number);
  ASSERT_EQ(error.GetNearString(), near_string);
}

