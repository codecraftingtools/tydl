#ifndef GENERATED_PARENT_HPP
#define GENERATED_PARENT_HPP

#include <generated/Child.hpp>
#include <tydl/Field.hpp>
#include <strings.h> // bzero

class Parent;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,Parent,byte_offset> :
    public tydl::Accessor<P,Parent,byte_offset> {
 public:
  using Accessor<P,Parent,byte_offset>::operator=;
  using This_ = tydl::Field<P,Parent,byte_offset>;
  Field() {bzero(this, sizeof(this));}
  union {
    Field<This_,Child,byte_offset+0> child1;
    Field<This_,Child,byte_offset+8> child2;
  };
};

class Parent : public tydl::Field<Parent> {};

#endif // GENERATED_PARENT_HPP
