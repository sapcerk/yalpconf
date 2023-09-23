#ifndef YALPCONF_SRC_READER_FILE_READER_H_
#define YALPCONF_SRC_READER_FILE_READER_H_

#include <string>

#include "reader/reader.h"
#include "reader/buffer.h"

namespace yalpconf {

class FileReader : public Reader {
  public:
    explicit FileReader(const std::string& file_name);
    Buffer ReadConfiguration() override;
  private:
    const std::string file_name_;
};

} // namespace yalpconf

#endif // YALPCONF_SRC_READER_FILE_READER_H_
