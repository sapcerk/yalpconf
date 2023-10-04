#ifndef YALPCONF_SRC_READER_STRING_READER_H_
#define YALPCONF_SRC_READER_STRING_READER_H_

#include <string>

#include "error.h"
#include "reader/reader.h"

namespace yalpconf {

class StringReader : public Reader {
  public:
    StringReader(const std::string& input_str);
    StringReader(std::string&& input_str) noexcept;
    ~StringReader() = default;
    Error ReadConfiguration() override;
    bool empty() const override;
    char TakeNextSymbol() const override;
    char CheckNextSymbol() const override;
  private:
    const std::string input_str_;
    mutable size_t next_symbol_position_;
};

} // namespace yalpconf

#endif // YALPCONF_SRC_READER_STRING_READER_H_
