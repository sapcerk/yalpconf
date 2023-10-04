#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "error.h"
#include "reader/reader.h"
#include "reader/blocking_file_reader.h"

namespace yalpconf {

BlockingFileReader::BlockingFileReader(const std::string& file_name) 
    : file_name_ { file_name }, next_symbol_position_ { 0 } {};
  
Error BlockingFileReader::ReadConfiguration() {
  std::ifstream configuration_file(file_name_, std::ios::binary | std::ios::in);
  if (!configuration_file.is_open()) {
    return Error(ErrorCode::CantOpenFile);
  }
  configuration_file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize size { configuration_file.gcount() };
  data_.resize(size);
  configuration_file.seekg(0);
  configuration_file.read(data_.data(), size);
  configuration_file.close();
  return Error(ErrorCode::None);
}

bool BlockingFileReader::empty() const {
  return next_symbol_position_ >= data_.size();
}

char BlockingFileReader::TakeNextSymbol() const {
  return data_[next_symbol_position_++];
}

char BlockingFileReader::CheckNextSymbol() const {
  return data_[next_symbol_position_];
}

} // namespace yalpconf
