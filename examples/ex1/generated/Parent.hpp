#ifndef GENERATED_PARENT_HPP
#define GENERATED_PARENT_HPP

#include <generated/Child.hpp>
#include <tydl/Field.hpp>
#include <tydl/Concrete.hpp>

class Parent;

namespace tydl {

template<size_t byte_offset, size_t bit_offset>
class Members<Parent,byte_offset,bit_offset>
{
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  using child1_t_ = Child;
  using child2_t_ = Child;
  
  union {
    Field<
      Members,
      Concrete<
        child1_t_,
        byte_offset,
        bit_offset>
      > child1;
    Field<
      Members,
      Concrete<
        child2_t_,
        byte_offset + num_bytes_allocated_for<child1_t_>(),
        bit_offset>
      > child2;
  };

  const static size_t num_allocated_bytes_ {
    num_bytes_allocated_for<typeof(child1)>() +
    num_bytes_allocated_for<typeof(child2)>()
  };
  
  size_t get_num_bytes_() const {
    return num_bytes_allocated_for<Parent>();
  }
};

} // namespace tydl

class Parent : public tydl::Field<tydl::Concrete<Parent>> {
 public:
  using tydl::Field<tydl::Concrete<Parent>>::Field;
  using tydl::Field<tydl::Concrete<Parent>>::operator=;
  
  ~Parent() {}
  Parent() { memset(this, 0, tydl::num_bytes_allocated_for<Parent>()); }
  Parent(const Parent &other) { set_(other); }
  Parent(Parent &&) = delete;
  Parent &operator=(const Parent &other) { set_(other); return *this; };
  Parent &operator=(Parent &&) = delete;
  
 private:
  uint8_t data_bytes_[num_allocated_bytes_-1];
};

#endif // GENERATED_PARENT_HPP
