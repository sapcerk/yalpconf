#ifndef YALPCONF_SRC_READER_BUFFER_H_
#define YALPCONF_SRC_READER_BUFFER_H_

#include <iostream>

namespace yalpconf {

class Buffer {
  public:
    explicit Buffer(size_t size);
    ~Buffer();

    char* data();
    size_t size() const;
    char operator[](size_t position) const;
  private:
    size_t size_;
    char* data_;
};

} // namespace yalpconf


#endif // YALPCONF_SRC_READER_BUFFER_H_
