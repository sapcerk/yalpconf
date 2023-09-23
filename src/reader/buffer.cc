#include <iostream>
#include <algorithm>

#include "reader/buffer.h"

namespace yalpconf {

Buffer::Buffer(size_t size) 
    : size_ { size } {
  if (size > 0) {
    data_ = new char[size];
  } else {
    data_ = nullptr;
  }
}

Buffer::~Buffer() {
  if(data_)
    delete[] data_;
}

Buffer::Buffer(const Buffer& other) noexcept {
  size_ = other.size_; 
  if (size_ > 0) {
    data_ = new char[size_];
    std::copy(other.data_, other.data_ + size_, data_);
  } else {
    data_ = nullptr;
  }
}

Buffer& Buffer::operator=(const Buffer& other) noexcept {
  if (this != &other) {
    if (data_)
      delete[] data_;
    size_ = other.size_; 
    if (size_ > 0) {
      data_ = new char[size_];
      std::copy(other.data_, other.data_ + size_, data_);
    } else {
      data_ = nullptr;
    }
  }
  return *this;
}

Buffer::Buffer(Buffer&& other) noexcept {
  size_ = other.size_; 
  data_ = other.data_;
  other.size_ = 0;
  other.data_ = nullptr;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
  if (this != &other) {
    if (data_)
      delete[] data_;
    size_ = other.size_; 
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

char* Buffer::data() {
  return data_;
}

size_t Buffer::size() const {
  return size_;
}

bool Buffer::empty() const {
  return (size_ == 0);
}

char Buffer::operator[](size_t position) const {
  return data_[position];
}

} // namespace yalpconf
