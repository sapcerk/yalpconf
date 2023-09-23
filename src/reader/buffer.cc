#include <iostream>

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
