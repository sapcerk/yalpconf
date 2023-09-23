#ifndef YALPCONF_SRC_READER_READER_H_
#define YALPCONF_SRC_READER_READER_H_

#include "reader/buffer.h"

namespace yalpconf {

class Reader {
  public:
    virtual Buffer ReadConfiguration() = 0;
};

} // namespace yalpconf


#endif // YALPCONF_SRC_READER_READER_H_
