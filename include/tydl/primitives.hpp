// Copyright 2021 Jeffrey A. Webb

#ifndef TYDL_PRIMITIVES_HPP
#define TYDL_PRIMITIVES_HPP

#include <cstdint>
#include <cstddef> // std::size_t
#include <array>

namespace tydl {

using size_t = std::size_t;

using UInt8 = uint8_t;

template<typename T, size_t I>
struct Array : public std::array<T,I> {
  const static size_t num_allocated_bytes_ { sizeof(Array) };
};

} // namespace tydl

#endif // TYDL_PRIMITIVES_HPP
