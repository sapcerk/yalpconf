#include <iostream>

#include "config.h"

template <typename T>
void PrintSettingAs(std::shared_ptr<yalpconf::Object> object,
                    const std::string key) {
  if (object->exist(key) && 
      object->value(key)->Is<T>()) {
    std::cout << "Setting found. Key: " << key << "; Value: " << 
      object->value(key)->As<T>().value() << std::endl;
  } else {
    std::cout << "Setting with name '" << key <<
        "' does not exist or have different type." << std::endl;
  }
}

template <typename T>
void PrintSettingAs(const yalpconf::Object& object,
                    const std::string key) {
  if (object.exist(key) && 
      object.value(key)->Is<T>()) {
    std::cout << "Setting found. Key: " << key << "; Value: " << 
      object.value(key)->As<T>().value() << std::endl;
  } else {
    std::cout << "Setting with name '" << key <<
        "' does not exist or have different type." << std::endl;
  }
}

int main() {
  yalpconf::Config cfg("example.conf");
  yalpconf::Error error { cfg.ReadConfiguration() };
  if (error.GetCode() != yalpconf::ErrorCode::None) {
    std::cout << "Error message: " << error.GetMessage() << std::endl;
    return 0;
  }
  auto root = cfg.GetRootObject();
  // get setting that does not exist
  PrintSettingAs<yalpconf::String>(root, "does_not_exist");
  // get setting contains string value
  PrintSettingAs<yalpconf::String>(root, "setting-string");
  // get setting contains boolean value
  PrintSettingAs<yalpconf::Boolean>(root, "setting-boolean");
  // get setting contains int value
  PrintSettingAs<yalpconf::Int>(root, "setting-int");
  // get setting contains array of int value
  std::string key { "array-int" };
  if (root->exist(key) && 
      root->value(key)->Is<yalpconf::Array>()) {
    std::cout << "Setting found. Key: " << key << "; Values:";
    auto array = root->value(key)->As<yalpconf::Array>();
    for (size_t i{}; i < array.size(); ++i) {
      std::cout << " " << array[i]->As<yalpconf::Int>().value();
    }
    std::cout << std::endl;
  } else {
    std::cout << "Setting with name '" << key <<
        "' does not exist or have different type." << std::endl;
  }
  // get setting contains object of settings
  key = "object";
  if (root->exist(key) && 
      root->value(key)->Is<yalpconf::Object>()) {
    std::cout << "Setting found. Key: " << key << "; Object contains: " << std::endl;
    auto object = root->value(key)->As<yalpconf::Object>();
    // get setting contains boolean value
    PrintSettingAs<yalpconf::Boolean>(object, "_boolean");
    // get setting contains array of mixed values
    std::string key { "array-mixed" };
    if (object.exist(key) && 
        object.value(key)->Is<yalpconf::Array>()) {
      std::cout << "Setting found. Key: " << key << "; Values count: ";
      auto array = object.value(key)->As<yalpconf::Array>();
      std::cout << array.size() << "; Values:";
      std::cout << " " << array[0]->As<yalpconf::Int>().value();
      std::cout << " " << array[1]->As<yalpconf::String>().value();
      std::cout << " " << array[2]->As<yalpconf::Boolean>().value();
      std::cout << std::endl;
    } else {
      std::cout << "Setting with name '" << key <<
          "' does not exist or have different type." << std::endl;
    }
  } else {
    std::cout << "Setting with name '" << key <<
        "' does not exist or have different type." << std::endl;
  }
/*
{
setting-string = "string 101";
setting-boolean = False;
setting-int = 0;
array-int = [ 101, 0x65, 0b1100101 ];
object = {
  boolean = true;
  array-mixed = [ 101, "str", false ];
}
}
*/
  return 0;
}
