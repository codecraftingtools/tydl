#ifndef TYDL_SIZING_HPP
#define TYDL_SIZING_HPP

#include <tydl/locators.hpp>

namespace tydl {

template<typename Type, class Sizer>
class Sizing {
 public:
  ~Sizing() {}
  Sizing() {}
  Sizing(const Sizing &) = delete;
  Sizing(Sizing &&) = delete;
  Sizing &operator=(const Sizing &) = delete;
  Sizing &operator=(Sizing &&) = delete;

  const static size_t num_allocated_bytes_ { sizeof(Type) };

  size_t get_num_bytes_() const {
    Sizer sizer;
    return sizer(this);
  }
};

} // namespace tydl

#endif // TYDL_SIZING_HPP
