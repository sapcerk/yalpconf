#ifndef YALPCONF_SRC_READER_BLOCKING_FILE_READER_H_
#define YALPCONF_SRC_READER_BLOCKING_FILE_READER_H_

#include <string>
#include <vector>

#include "error.h"
#include "reader/reader.h"

namespace yalpconf {

class BlockingFileReader : public Reader {
  public:
    explicit BlockingFileReader(const std::string& file_name);
    ~BlockingFileReader() = default;
    Error ReadConfiguration() override;
    bool empty() const override;
    char TakeNextSymbol() const override;
    char CheckNextSymbol() const override;
  private:
    const std::string file_name_;
    mutable size_t next_symbol_position_;
    std::vector<char> data_;
};

} // namespace yalpconf

#endif // YALPCONF_SRC_READER_BLOCKING_FILE_READER_H_
