#ifndef TYDL_ACCESSOR_HPP
#define TYDL_ACCESSOR_HPP

#include <cstdint>

namespace tydl {

template<typename T, typename S>
class Accessor {
 public:
  typedef T Accessor_Type_;
  typedef S Accessor_Subclass_;
};

using size_t = uint32_t;

template<typename T>
constexpr size_t max_number_of_bytes_in() {
  return sizeof(T);
}

template<typename T>
size_t number_of_bytes_in(const T &t) {
  return max_number_of_bytes_in<T>();
}

} // namespace tydl

#endif // TYDL_ACCESSOR_HPP
