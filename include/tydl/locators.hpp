// Copyright 2021 Jeffrey A. Webb

#ifndef TYDL_LOCATORS_HPP
#define TYDL_LOCATORS_HPP

#include <tydl/functions.hpp>

namespace tydl {

template<size_t byte_offset=0>
struct Absolute {
  constexpr size_t operator()(const void *ptr) const {
    return byte_offset;
  }
};

using Beginning = Absolute<0>;

template<class Parent_Locator, size_t byte_offset=0>
struct Relative {
  size_t operator()(const void *ptr) const {
    Parent_Locator parent_locator;
    return parent_locator(ptr) + byte_offset;
  }
};

template<typename Type>
struct Allocated_Size {
  constexpr size_t operator()(const void *ptr) const {
    return num_bytes_allocated_for<Type>();
  }
};

} // namespace tydl

#endif // TYDL_LOCATORS_HPP
