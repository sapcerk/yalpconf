#ifndef YALPCONF_INCLUDE_TYPES_VALUE_H_
#define YALPCONF_INCLUDE_TYPES_VALUE_H_

#include <type_traits>
#include <typeinfo>
#include <concepts>

namespace yalpconf {

class Value;

template <typename T>
concept IsSameAsValue = std::is_same_v<T, Value>;

template <typename T>
concept IsDerivedFromValue = std::derived_from<T, Value>;

class Value {
  public:
    virtual ~Value() = 0;

    template <typename T>
        requires IsDerivedFromValue<T> && (!IsSameAsValue<T>)
    bool Is() { return typeid(T) == typeid(*this); }

    template <typename T>
        requires IsDerivedFromValue<T> && (!IsSameAsValue<T>)
    const T& As() { return dynamic_cast<const T&>(*this); }
};

inline Value::~Value() {}

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_TYPES_VALUE_H_
