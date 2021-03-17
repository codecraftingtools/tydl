#ifndef TYDL_MEMBERS_HPP
#define TYDL_MEMBERS_HPP

#include <tydl/functions.hpp>

namespace tydl {

template<typename Type, size_t byte_offset, size_t bit_offset>
class Members {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  const static size_t num_allocated_bytes_ {
    num_bytes_allocated_for<Type>()
  };

  size_t get_num_bytes_() const {
    return num_bytes_allocated_for<Type>();
  }
};

} // namespace tydl

#endif // TYDL_MEMBERS_HPP
