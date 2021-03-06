#ifndef GENERATED_PARENT_HPP
#define GENERATED_PARENT_HPP

#include <generated/Child.hpp>
#include <tydl/Field.hpp>

class Parent;

namespace tydl {

template<>
constexpr size_t max_number_of_bytes_in<Parent>() { return 16; }

template<typename P, size_t byte_offset>
class Field<P,Parent,byte_offset> :
      public accessors::Field<P,Parent,byte_offset>
{
 public:
  using accessors::Field<P,Parent,byte_offset>::Field;
  using accessors::Field<P,Parent,byte_offset>::operator=;
  
  ~Field() {}
  Field() {}
  Field(const Field &f) { (*this)(f()); }
  Field(Field &&) = delete;
  Field &operator=(const Field &f) { (*this)(f()); return *this; };
  Field &operator=(Field &&) = delete;

  using This_ = Field<P,Parent,byte_offset>;
  union {
    Field<This_,Child,byte_offset+0> child1;
    Field<This_,Child,byte_offset+sizeof(Child)> child2;
  };
};

} // namespace tydl

class Parent : public tydl::Field<Parent> {
 public:
  using tydl::Field<Parent>::Field;
  using tydl::Field<Parent>::operator=;
  
  ~Parent() {}
  Parent() { memset(this, 0, tydl::max_number_of_bytes_in<Parent>()); }
  Parent(const Parent &o) { (*this)(o()); }
  Parent(Parent &&) = delete;
  Parent &operator=(const Parent &o) { (*this)(o()); return *this; };
  Parent &operator=(Parent &&) = delete;
  
 private:
  uint8_t tydl_data_bytes_[tydl::max_number_of_bytes_in<Parent>()-1];
};

#endif // GENERATED_PARENT_HPP
