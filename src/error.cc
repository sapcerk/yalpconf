#include <string>

#include "error.h"

namespace yalpconf {

Error::Error()
    : code_ { ErrorCode::None }, line_ { 0 } {}

Error::Error(ErrorCode code)
    : code_ { code }, line_ { 0 } {}

Error::Error(ErrorCode code, size_t line)
    : code_ { code }, line_ { line } {}

Error::Error(ErrorCode code, size_t line, std::string near_string)
    : code_ { code }, line_ { line }, near_string_ { near_string } {}

Error::Error(ErrorCode code, size_t line, char near_string)
    : code_ { code }, line_ { line }, 
      near_string_ { std::string(1, near_string) } {}

Error::Error(ErrorCode code, size_t line, 
    std::string near_string, std::string expected_string)
    : code_ { code }, line_ { line }, 
      near_string_ { near_string }, expected_string_ { expected_string } {}

Error::Error(const Error& other) {
  code_ = other.code_;
  line_ = other.line_;
  near_string_ = other.near_string_;
  expected_string_ = other.expected_string_;
}

Error::Error(Error&& other) noexcept {
  code_ = std::move(other.code_);
  line_ = std::move(other.line_);
  near_string_ = std::move(other.near_string_);
  expected_string_ = std::move(other.expected_string_);
  other.code_ = ErrorCode::None;
  other.line_ = 0;
  other.near_string_ = std::string();
  other.expected_string_ = std::string();
}

ErrorCode Error::GetCode() const {
  return code_;
}

int Error::GetCodeInt() const {
  return static_cast<int>(code_);
}

size_t Error::GetLine() const {
  return line_;
}

std::string Error::GetNearString() const {
  return near_string_;
}

std::string Error::GetExpectedString() const {
  return expected_string_;
}

std::string Error::GetMessage() const {
  return ("Error occurred on line: " + std::to_string(line_) +
      ". Near string: " + near_string_ + ". Expected: " + expected_string_ +
      ". Desctiption: " + message_.at(code_));
}

Error& Error::operator=(const Error& other) {
  if (this != &other) {
    code_ = other.code_;
    line_ = other.line_;
    near_string_ = other.near_string_;
    expected_string_ = other.expected_string_;
  }
  return *this;
}

Error& Error::operator=(Error&& other) noexcept {
  if (this != &other) {
    code_ = std::move(other.code_);
    line_ = std::move(other.line_);
    near_string_ = std::move(other.near_string_);
    expected_string_ = std::move(other.expected_string_);
    other.code_ = ErrorCode::None;
    other.line_ = 0;
    other.near_string_ = std::string();
    other.expected_string_ = std::string();
  }
  return *this;
}

} // namespace yalpconf 
