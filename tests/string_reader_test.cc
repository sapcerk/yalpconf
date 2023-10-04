#include <gtest/gtest.h>

#include <string>

#include "error.h"
#include "reader/reader.h"
#include "reader/string_reader.h"


TEST(BlockingFileReaderTests, TestReadFromStringViaInterfaceMove) {
  const std::string content { R"(line = "str",
array = [ 1; 2, 3 ];
obj = { set = true };

)" };
  std::string content_move { content };
  std::unique_ptr<yalpconf::Reader> reader { std::make_unique<yalpconf::StringReader>(std::move(content_move)) };
  yalpconf::Error error = reader->ReadConfiguration(); 
  ASSERT_EQ(error.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_EQ(reader->empty(), false); 
  for (size_t i{}; i < content.size(); ++i) {
    ASSERT_FALSE(reader->empty());
    ASSERT_EQ(reader->CheckNextSymbol(), content[i]);
    ASSERT_EQ(reader->TakeNextSymbol(), content[i]);
  }
}

TEST(BlockingFileReaderTests, TestReadFromStringViaInterface) {
  const std::string content { R"(line = "str",
array = [ 1; 2, 3 ];
obj = { set = true };

)" };
  std::unique_ptr<yalpconf::Reader> reader { std::make_unique<yalpconf::StringReader>(content) };
  yalpconf::Error error = reader->ReadConfiguration(); 
  ASSERT_EQ(error.GetCode(), yalpconf::ErrorCode::None); 
  ASSERT_EQ(reader->empty(), false); 
  for (size_t i{}; i < content.size(); ++i) {
    ASSERT_FALSE(reader->empty());
    ASSERT_EQ(reader->CheckNextSymbol(), content[i]);
    ASSERT_EQ(reader->TakeNextSymbol(), content[i]);
  }
}
