#ifndef TYDL_CONCRETE_HPP
#define TYDL_CONCRETE_HPP

#include <tydl/Members.hpp>
#include <cstring> // memcpy

namespace tydl {

template <typename Type, class Locator, class Sizer=Allocated_Size<Type>>
class Concrete : public Members<Type,Locator,Sizer> {
 public:
  ~Concrete() {}
  Concrete() {}
  Concrete(const Concrete &) = delete;
  Concrete(Concrete &&) = delete;
  Concrete &operator=(const Concrete &) = delete;
  Concrete &operator=(Concrete &&) = delete;

  const Type &get_() const {
    Locator locator;
    size_t byte_offset = locator(this);
    return *reinterpret_cast<const Type*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  
  void set_(const Type &value) {
    Locator locator;
    size_t byte_offset = locator(this);
    memcpy(reinterpret_cast<uint8_t*>(this) + byte_offset,
           &value, num_bytes_in(value));
  }
};

} // namespace tydl

#endif // TYDL_CONCRETE_HPP
