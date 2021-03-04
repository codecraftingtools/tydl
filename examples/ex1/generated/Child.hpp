#ifndef GENERATED_CHILD_HPP
#define GENERATED_CHILD_HPP

#include <tydl/Field.hpp>
#include <cstdint>
#include <cstring> // memset

class Child;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,Child,byte_offset> :
    public tydl::Accessor<P,Child,byte_offset> {
 public:
  using Accessor<P,Child,byte_offset>::Accessor;
  using Accessor<P,Child,byte_offset>::operator=;
  
  ~Field() {}
  Field() {}
  Field(const Field &) = delete;
  Field(Field &&) = delete;
  Field &operator=(const Field &f) {
    Accessor<P,Child,byte_offset>::operator=(f);
    return *this;
  }
  Field &operator=(Field &&) = delete;

  using This_ = tydl::Field<P,Child,byte_offset>;
  union {
    Field<This_,uint32_t,byte_offset+0> member1;
    Field<This_,uint32_t,byte_offset+sizeof(uint32_t)> member2;
  };
};

class Child : public tydl::Field<Child> {
 public:
  using tydl::Field<Child>::Field;
  using tydl::Field<Child>::operator=;
  
  ~Child() {}
  Child() {
    memset(this, 0, sizeof(*this));
  }
  Child(const Child &c) {
    *this = c;
  }
  Child(Child &&) = delete;
  Child &operator=(const Child &c) {
    Field<Child>::operator=(c);
    return *this;
  }
  Child &operator=(Child &&) = delete;
};

#endif // GENERATED_CHILD_HPP
