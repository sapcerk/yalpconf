#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "reader/buffer.h"
#include "reader/reader.h"
#include "reader/file_reader.h"

TEST(FileReaderTests, TestOpenNoExistFile) {
  yalpconf::FileReader reader("no_exist.conf");
  yalpconf::Buffer buffer { reader.ReadConfiguration() }; 
  ASSERT_EQ(buffer.empty(), true); 
}

TEST(FileReaderTests, TestReadEmptyFile) {
  yalpconf::FileReader reader("file_reader_test_read_empty_file.conf");
  yalpconf::Buffer buffer { reader.ReadConfiguration() }; 
  ASSERT_EQ(buffer.empty(), true); 
  ASSERT_EQ(buffer.size(), 0); 
}

TEST(FileReaderTests, TestReadFile) {
  const std::string test_file_content { R"(line = "str"
array = [ 1, 2, 3 ];
obj = { set = true }

)" };
  yalpconf::FileReader reader("file_reader_test_read_file.conf");
  yalpconf::Buffer buffer { reader.ReadConfiguration() }; 
  ASSERT_EQ(buffer.size(), test_file_content.size());
  for(int i{}; i < test_file_content.size(); ++i) {
    ASSERT_EQ(buffer[i], test_file_content[i]);
  }
}
