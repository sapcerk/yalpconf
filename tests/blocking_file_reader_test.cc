#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <memory>

#include "error.h"
#include "reader/reader.h"
#include "reader/blocking_file_reader.h"

TEST(BlockingFileReaderTests, TestOpenNoExistFile) {
  yalpconf::BlockingFileReader reader("no_exist.conf");
  yalpconf::Error err = reader.ReadConfiguration(); 
  ASSERT_EQ(err.GetCode(), yalpconf::ErrorCode::CantOpenFile); 
  ASSERT_EQ(reader.empty(), true); 
}

TEST(BlockingFileReaderTests, TestReadEmptyFile) {
  yalpconf::BlockingFileReader reader("empty.conf");
  yalpconf::Error err = reader.ReadConfiguration(); 
  ASSERT_EQ(err.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_EQ(reader.empty(), true); 
}

TEST(BlockingFileReaderTests, TestReadFile) {
  const std::string test_file_content { R"(line = "str",
array = [ 1; 2, 3 ];
obj = { set = true };

)" };
  yalpconf::BlockingFileReader reader("example.conf");
  yalpconf::Error error = reader.ReadConfiguration(); 
  ASSERT_EQ(error.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_EQ(reader.empty(), false); 
  for (size_t i{}; i < test_file_content.size(); ++i) {
    ASSERT_FALSE(reader.empty());
    ASSERT_EQ(reader.CheckNextSymbol(), test_file_content[i]);
    ASSERT_EQ(reader.TakeNextSymbol(), test_file_content[i]);
  }
}

TEST(BlockingFileReaderTests, TestReadFileViaInterface) {
  const std::string test_file_content { R"(line = "str",
array = [ 1; 2, 3 ];
obj = { set = true };

)" };
  std::unique_ptr<yalpconf::Reader> reader { std::make_unique<yalpconf::BlockingFileReader>("example.conf") };
  yalpconf::Error error = reader->ReadConfiguration(); 
  ASSERT_EQ(error.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_EQ(reader->empty(), false); 
  for (size_t i{}; i < test_file_content.size(); ++i) {
    ASSERT_FALSE(reader->empty());
    ASSERT_EQ(reader->CheckNextSymbol(), test_file_content[i]);
    ASSERT_EQ(reader->TakeNextSymbol(), test_file_content[i]);
  }
}
