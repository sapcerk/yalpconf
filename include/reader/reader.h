#ifndef YALPCONF_SRC_READER_READER_H_
#define YALPCONF_SRC_READER_READER_H_

#include "error.h"

namespace yalpconf {

class Reader {
  public:
    virtual ~Reader() = default;
    virtual Error ReadConfiguration() = 0;
    virtual bool empty() const = 0;
    virtual char TakeNextSymbol() const = 0;
    virtual char CheckNextSymbol() const = 0;
};

} // namespace yalpconf


#endif // YALPCONF_SRC_READER_READER_H_
