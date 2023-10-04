#include <string>

#include "error.h"
#include "reader/reader.h"
#include "reader/string_reader.h"

namespace yalpconf {

StringReader::StringReader(const std::string& input_str) 
    : input_str_ { input_str }, next_symbol_position_ { 0 } {};

StringReader::StringReader(std::string&& input_str) noexcept 
    : input_str_ { std::move(input_str) }, next_symbol_position_ { 0 } {};
  
Error StringReader::ReadConfiguration() {
  return Error(ErrorCode::None);
}

bool StringReader::empty() const {
  return next_symbol_position_ >= input_str_.size();
}

char StringReader::TakeNextSymbol() const {
  return input_str_[next_symbol_position_++];
}

char StringReader::CheckNextSymbol() const {
  return input_str_[next_symbol_position_];
}

} // namespace yalpconf
