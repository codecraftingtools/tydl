#ifndef TYDL_ACCESSOR_HPP
#define TYDL_ACCESSOR_HPP

#include <cstdint>

namespace tydl {

using size_t = uint32_t;

template<class P, class T=P, size_t byte_offset=0>
class Accessor {
 public:
  const T &operator()() const {
    return *reinterpret_cast<const T*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  P &operator()(const T &value) {
    *reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(this) + byte_offset) = value;
    return *reinterpret_cast<P*>(this);
  }
  T operator=(const T &value) {
    *reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(this) + byte_offset) = value;
    return value;
  }
  template<class P2, size_t byte_offset2=0>
  T operator=(const Accessor<P2,T,byte_offset2> &a) {
    auto value = a();
    *reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(this) + byte_offset) = value;
    return value;
  }
};

} // namespace tydl

#endif // TYDL_ACCESSOR_HPP
