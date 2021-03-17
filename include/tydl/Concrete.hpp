#ifndef TYDL_CONCRETE_HPP
#define TYDL_CONCRETE_HPP

#include <tydl/Members.hpp>
#include <cstring> // memcpy

namespace tydl {

template <typename Type, size_t byte_offset=0, size_t bit_offset=0>
class Concrete : public Members<Type,byte_offset,bit_offset> {
 public:
  using Type_ = Type;
  
  ~Concrete() {}
  Concrete() {}
  Concrete(const Concrete &) = delete;
  Concrete(Concrete &&) = delete;
  Concrete &operator=(const Concrete &) = delete;
  Concrete &operator=(Concrete &&) = delete;

  const Type &get_() const {
    return *reinterpret_cast<const Type*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  
  void set_(const Type &value) {
    memcpy(reinterpret_cast<uint8_t*>(this) + byte_offset,
           &value, num_bytes_in(value));
  }
};

} // namespace tydl

#endif // TYDL_CONCRETE_HPP
