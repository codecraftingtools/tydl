#ifndef GENERATED_PARENT_HPP
#define GENERATED_PARENT_HPP

#include <generated/Child.hpp>
#include <tydl/Field.hpp>
#include <cstring> // memset

class Parent;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,Parent,byte_offset> :
    public tydl::Accessor<P,Parent,byte_offset> {
 public:
  using Accessor<P,Parent,byte_offset>::Accessor;
  using Accessor<P,Parent,byte_offset>::operator=;
  
  ~Field() {}
  Field() {}
  Field(const Field &) = delete;
  Field(Field &&) = delete;
  Field &operator=(const Field &f) {
    Accessor<P,Parent,byte_offset>::operator=(f);
    return *this;
  }
  Field &operator=(Field &&) = delete;

  using This_ = tydl::Field<P,Parent,byte_offset>;
  union {
    Field<This_,Child,byte_offset+0> child1;
    Field<This_,Child,byte_offset+sizeof(Child)> child2;
  };
};

class Parent : public tydl::Field<Parent> {
 public:
  using tydl::Field<Parent>::Field;
  using tydl::Field<Parent>::operator=;

  ~Parent() {}
  Parent() {
    memset(this, 0, sizeof(*this));
  }
  Parent(const Parent &p) {
    *this = p;
  }
  Parent(Parent &&) = delete;
  Parent &operator=(const Parent &p) {
    Field<Parent>::operator=(p);
    return *this;
  }
  Parent &operator=(Parent &&) = delete;
};

#endif // GENERATED_PARENT_HPP
