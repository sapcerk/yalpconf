#include <gtest/gtest.h>

#include <string>

#include "reader/buffer.h"

TEST(BufferTests, TestBufferSizeNoEmpty) {
  const size_t size = 4;
  yalpconf::Buffer buffer(size);
  ASSERT_EQ(buffer.size(), size);
  ASSERT_EQ(buffer.empty(), false);
}

TEST(BufferTests, TestBufferEmpty) {
  yalpconf::Buffer buffer(0);
  ASSERT_EQ(buffer.empty(), true);
}

TEST(BufferTests, TestBufferWrite) {
  std::string str_to_write = "write";
  yalpconf::Buffer buffer(str_to_write.size());
  std::copy(str_to_write.data(), str_to_write.data() + str_to_write.size(), buffer.data());
  buffer.data()[1] = ' ';
  str_to_write[1] = ' ';
  ASSERT_STREQ(buffer.data(), str_to_write.c_str());
}

TEST(BufferTests, TestBufferRead) {
  const size_t size = 4;
  std::string str_to_write = "read";
  yalpconf::Buffer buffer(size);
  std::copy(str_to_write.data(), str_to_write.data() + str_to_write.size(), buffer.data());
  std::string str_to_read;
  for (size_t i{}; i < buffer.size(); ++i) {
    str_to_read.push_back(buffer[i]);
  }
  ASSERT_STREQ(str_to_read.c_str(), str_to_write.c_str());
}


TEST(BufferTests, TestBufferCopyMove) {
  std::string str = "test\0";
  auto copy_elison = [&str]() {
    yalpconf::Buffer buffer(str.size());
    std::copy(str.data(), str.data() + str.size(), buffer.data());
    return buffer;
  };
  yalpconf::Buffer buffer { copy_elison() };
  ASSERT_STREQ(buffer.data(), str.c_str());

  yalpconf::Buffer buffer_copy_constructor(buffer);
  ASSERT_STREQ(buffer_copy_constructor.data(), str.c_str());

  yalpconf::Buffer buffer_copy_assignment(0);
  buffer_copy_assignment = buffer_copy_constructor;
  ASSERT_STREQ(buffer_copy_assignment.data(), str.c_str());

  yalpconf::Buffer buffer_move_constructor(std::move(buffer));
  ASSERT_TRUE(buffer.data() == nullptr);
  ASSERT_STREQ(buffer_move_constructor.data(), str.c_str());

  yalpconf::Buffer buffer_move_assignment(0);
  buffer_move_assignment = std::move(buffer_move_constructor);
  ASSERT_TRUE(buffer_move_constructor.data() == nullptr);
  ASSERT_STREQ(buffer_move_assignment.data(), str.c_str());
}
