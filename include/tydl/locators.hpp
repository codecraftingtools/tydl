#ifndef TYDL_LOCATORS_HPP
#define TYDL_LOCATORS_HPP

#include <tydl/primitives.hpp>

namespace tydl {

template<size_t byte_offset=0>
struct Absolute {
  constexpr size_t operator()(const void *ptr) {
    return byte_offset;
  }
};

using Beginning = Absolute<0>;

template<class Parent_Locator, size_t byte_offset=0>
struct Relative {
  size_t operator()(const void *ptr) {
    Parent_Locator parent_locator;
    return parent_locator(ptr) + byte_offset;
  }
};

} // namespace tydl

#endif // TYDL_LOCATORS_HPP
