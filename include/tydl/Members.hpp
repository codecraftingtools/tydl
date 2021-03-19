#ifndef TYDL_MEMBERS_HPP
#define TYDL_MEMBERS_HPP

#include <tydl/Sizing.hpp>

namespace tydl {

template<typename Type, class Parent_Locator>
class Members : public Sizing<Type> {
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
    
} // namespace tydl

#endif // TYDL_MEMBERS_HPP
