#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "reader/reader.h"
#include "reader/file_reader.h"
#include "reader/buffer.h"

namespace yalpconf {

FileReader::FileReader(const std::string& file_name) 
    : file_name_ { file_name } {};
  
Buffer FileReader::ReadConfiguration() {
  std::ifstream configuration_file(file_name_, std::ios::binary | std::ios::in);
  if (configuration_file.is_open()) {
    configuration_file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize size { configuration_file.gcount() };
    Buffer buffer(size);
    configuration_file.seekg(0);
    configuration_file.read(buffer.data(), size);
    configuration_file.close();
    return buffer;
  }
  return Buffer(0);
}

} // namespace yalpconf
