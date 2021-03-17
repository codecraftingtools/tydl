#ifndef TYDL_FUNCTIONS_HPP
#define TYDL_FUNCTIONS_HPP

#include <tydl/primitives.hpp>
#include <type_traits> // enable_if_t

namespace tydl {

template<
  typename T,
  std::enable_if_t<std::is_integral_v<T>,T>* = nullptr>
constexpr size_t num_bytes_allocated_for() {
  return sizeof(T);
}

template<
  typename T,
  std::enable_if_t<std::is_floating_point_v<T>,T>* = nullptr>
constexpr size_t num_bytes_allocated_for() {
  return sizeof(T);
}

template<
  typename T,
  std::enable_if_t<std::is_class_v<T>,T>* = nullptr>
constexpr size_t num_bytes_allocated_for() {
  return T::num_allocated_bytes_;
}

//--------

template<typename T>
constexpr size_t num_bytes_allocated_for(const T &t) {
  return num_bytes_allocated_for<T>();
}

//--------

template<
  typename T,
  std::enable_if_t<std::is_integral_v<T>,T>* = nullptr>
size_t num_bytes_in(const T &t) {
  return num_bytes_allocated_for(t);
}

template<
  typename T,
  std::enable_if_t<std::is_floating_point_v<T>,T>* = nullptr>
size_t num_bytes_in(const T &t) {
  return num_bytes_allocated_for(t);
}

template<
  typename T,
  std::enable_if_t<std::is_class_v<T>,T>* = nullptr>
size_t num_bytes_in(const T &t)
{
  return t.get_num_bytes_();
}

} // namespace tydl

#endif // TYDL_FUNCTIONS_HPP
