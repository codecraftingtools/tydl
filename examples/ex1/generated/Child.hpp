#ifndef GENERATED_CHILD_HPP
#define GENERATED_CHILD_HPP

#include <tydl/Field.hpp>

class Child;

namespace tydl {

template<>
constexpr size_t max_number_of_bytes_in<Child>() { return 8; }

template<typename P, size_t byte_offset>
class Field<P,Child,byte_offset> :
      public accessors::Field<P,Child,byte_offset>
{
 public:
  using accessors::Field<P,Child,byte_offset>::Field;
  using accessors::Field<P,Child,byte_offset>::operator=;
  
  ~Field() {}
  Field() {}
  Field(const Field &f) { (*this)(f()); }
  Field(Field &&) = delete;
  Field &operator=(const Field &f) { (*this)(f()); return *this; };
  Field &operator=(Field &&) = delete;

  using This_ = Field<P,Child,byte_offset>;
  union {
    Field<This_,uint32_t,byte_offset+0> member1;
    Field<This_,uint32_t,byte_offset+sizeof(uint32_t)> member2;
  };
};

} // namespace tydl

class Child : public tydl::Field<Child> {
 public:
  using tydl::Field<Child>::Field;
  using tydl::Field<Child>::operator=;
  
  ~Child() {}
  Child() { memset(this, 0, tydl::max_number_of_bytes_in<Child>()); }
  Child(const Child &o) { (*this)(o()); }
  Child(Child &&) = delete;
  Child &operator=(const Child &o) { (*this)(o()); return *this; };
  Child &operator=(Child &&) = delete;
  
 private:
  uint8_t tydl_data_bytes_[tydl::max_number_of_bytes_in<Child>()-1];
};

#endif // GENERATED_CHILD_HPP
