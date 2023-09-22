#include <gtest/gtest.h>

#include <string>

#include "reader/buffer.h"

TEST(BufferTests, TestBufferSize) {
  const size_t size = 4;
  yalpconf::Buffer buffer(size);
  ASSERT_EQ(buffer.size(), size);
}

TEST(BufferTests, TestBufferWrite) {
  std::string str_to_write = "write";
  yalpconf::Buffer buffer(str_to_write.size());
  for (size_t i{}; i < str_to_write.size(); ++i) {
    buffer.data()[i] = str_to_write[i];
  }
  buffer.data()[1] = ' ';
  str_to_write[1] = ' ';
  ASSERT_STREQ(buffer.data(), str_to_write.c_str());
}

TEST(BufferTests, TestBufferRead) {
  const size_t size = 4;
  std::string str_to_write = "read";
  yalpconf::Buffer buffer(size);
  for (size_t i{}; i < str_to_write.size(); ++i) {
    buffer.data()[i] = str_to_write[i];
  }
  std::string str_to_read;
  for (size_t i{}; i < buffer.size(); ++i) {
    str_to_read.push_back(buffer[i]);
  }
  ASSERT_STREQ(str_to_read.c_str(), str_to_write.c_str());
}
