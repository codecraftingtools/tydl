#ifndef TYDL_MEMBERS_HPP
#define TYDL_MEMBERS_HPP

#include <tydl/Sizing.hpp>

namespace tydl {

template<typename Type, class Locator, class Sizer>
class Members : public Sizing<Type,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  union {
    uint8_t bytes_[num_bytes_allocated_for<Type>()];
  };
};
    
template<typename T, size_t I, class Locator, class Sizer>
class Members<Array<T,I>,Locator,Sizer> : public Sizing<Array<T,I>,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  const T &operator[](size_t i) const {
    Locator locator;
    auto *bptr = reinterpret_cast<const uint8_t*>(this) + locator(this);
    auto *ptr = reinterpret_cast<const Array<T,I>*>(bptr);
    return (*ptr)[i];
  }

  union {
    uint8_t bytes_[num_bytes_allocated_for<Array<T,I>>()];
  };
};
    
} // namespace tydl

#endif // TYDL_MEMBERS_HPP
