#ifndef TYDL_ACCESSOR_HPP
#define TYDL_ACCESSOR_HPP

#include <cstdint>
#include <cstring> // memcpy
#include <type_traits>

namespace tydl {

using size_t = uint32_t;

template<class P, typename T, size_t byte_offset>
class Accessor;

template<class P, typename T, size_t byte_offset>
class Field;

template<typename P, typename T, size_t byte_offset,
         typename P2, typename T2, size_t byte_offset2>
void set_accessor_value_(Accessor<P,T,byte_offset> &a,
                         const Field<P2,T2,byte_offset2> &value) {
  memcpy(reinterpret_cast<uint8_t*>(&a) + byte_offset,
         &value, sizeof(T));
}

template<typename P, typename T, size_t byte_offset, typename T2>
std::enable_if_t<std::is_integral_v<T2>,void>
set_accessor_value_(Accessor<P,T,byte_offset> &a, const T2 &value) {
  memcpy(reinterpret_cast<uint8_t*>(&a) + byte_offset,
         &value, sizeof(T));
}

template<typename P, typename T, size_t byte_offset, typename T2>
std::enable_if_t<std::is_floating_point_v<T2>,void>
set_accessor_value_(Accessor<P,T,byte_offset> &a, const T2 &value) {
  memcpy(reinterpret_cast<uint8_t*>(&a) + byte_offset,
         &value, sizeof(T));
}

template<class P, typename T=P, size_t byte_offset=0>
class Accessor {
 protected:
  ~Accessor() {}
  Accessor() {}
  Accessor(const T &t) {
    (*this)(t);
  }
  Accessor(const Accessor &a) {
    (*this)(a);
  }
  template<class P2, size_t byte_offset2>
  Accessor(const Accessor<P2,T,byte_offset2> &a) {
    (*this)(a);
  }
  Accessor(Accessor &&) = delete;
    
  Accessor &operator=(const T &t) {
    (*this)(t);
    return *this;
  }
  Accessor &operator=(const Accessor &a) {
    (*this)(a);
    return *this;
  }
  template<class P2, size_t byte_offset2=0>
  Accessor &operator=(const Accessor<P2,T,byte_offset2> &a) {
    (*this)(a);
    return *this;
  }
  Accessor &operator=(Accessor &&) = delete;

 public:
  const T &operator()() const {
    return *reinterpret_cast<const T*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  P &operator()(const T &value) {
    tydl::set_accessor_value_<P,T,byte_offset>(*this, value);
    return *reinterpret_cast<P*>(this);
  }
  template<class P2, size_t byte_offset2=0>
  P &operator()(const Accessor<P2,T,byte_offset2> &a) {
    return (*this)(a());
  }
};

} // namespace tydl

#endif // TYDL_ACCESSOR_HPP
