#ifndef YALPCONF_INCLUDE_CONFIG_H_
#define YALPCONF_INCLUDE_CONFIG_H_

#include <memory>
#include <string>

#include "error.h"
#include "types/object.h"
#include "types/array.h"
#include "types/int.h"
#include "types/string.h"
#include "types/boolean.h"

namespace yalpconf {

class Config {
  public: 
    Config(const std::string& file_name);
    Error ReadConfiguration();
    std::shared_ptr<Object> GetRootObject();
  private:
    std::string file_name_;
    std::shared_ptr<Object> root_object_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_CONFIG_H_
