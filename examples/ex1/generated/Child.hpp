#ifndef GENERATED_CHILD_HPP
#define GENERATED_CHILD_HPP

#include <tydl/Field.hpp>
#include <cstdint>
#include <strings.h> // bzero

class Child;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,Child,byte_offset> :
    public tydl::Accessor<P,Child,byte_offset> {
 public:
  using Accessor<P,Child,byte_offset>::operator=;
  using This_ = tydl::Field<P,Child,byte_offset>;
  Field() {bzero(this, sizeof(this));}
  union {
    Field<This_,uint32_t,byte_offset+0> member1;
    Field<This_,uint32_t,byte_offset+4> member2;
  };
};

class Child : public tydl::Field<Child> {};

#endif // GENERATED_CHILD_HPP
