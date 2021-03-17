#ifndef GENERATED_CHILD_HPP
#define GENERATED_CHILD_HPP

#include <tydl/Field.hpp>
#include <tydl/Concrete.hpp>

class Child;

namespace tydl {

template<size_t byte_offset, size_t bit_offset>
class Members<Child,byte_offset,bit_offset>
{
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  using member1_t_ = uint32_t;
  using member2_t_ = uint32_t;
  
  union {
    Field<
      Members,
      Concrete<
        member1_t_,
        byte_offset,
        bit_offset>
      > member1;
    Field<
      Members,
      Concrete<
        member2_t_,
        byte_offset + num_bytes_allocated_for<member1_t_>(),
        bit_offset>
      > member2;
  };

  const static size_t num_allocated_bytes_ {
    num_bytes_allocated_for<typeof(member1)>() +
    num_bytes_allocated_for<typeof(member2)>()
  };
  
  size_t get_num_bytes_() const {
    return num_bytes_allocated_for<Child>();
  }
};

} // namespace tydl

class Child : public tydl::Field<tydl::Concrete<Child>> {
 public:
  using tydl::Field<tydl::Concrete<Child>>::Field;
  using tydl::Field<tydl::Concrete<Child>>::operator=;
  
  ~Child() {}
  Child() { memset(this, 0, tydl::num_bytes_allocated_for<Child>()); }
  Child(const Child &other) { set_(other); }
  Child(Child &&) = delete;
  Child &operator=(const Child &other) { set_(other); return *this; };
  Child &operator=(Child &&) = delete;
  
 private:
  uint8_t data_bytes_[num_allocated_bytes_-1];
};

#endif // GENERATED_CHILD_HPP
