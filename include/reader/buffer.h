#ifndef YALPCONF_SRC_READER_BUFFER_H_
#define YALPCONF_SRC_READER_BUFFER_H_

namespace yalpconf {

class Buffer {
  public:
    explicit Buffer(size_t size);
    ~Buffer();

    Buffer(const Buffer& other) noexcept;
    Buffer& operator=(const Buffer& other) noexcept;

    Buffer(Buffer&& other) noexcept;
    Buffer& operator=(Buffer&& other) noexcept;

    char* data();
    size_t size() const;
    bool empty() const;
    char operator[](size_t position) const;
  private:
    size_t size_;
    char* data_;
};

} // namespace yalpconf


#endif // YALPCONF_SRC_READER_BUFFER_H_
