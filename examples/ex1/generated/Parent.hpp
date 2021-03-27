#ifndef GENERATED_PARENT_HPP
#define GENERATED_PARENT_HPP

#include <generated/Child.hpp>
#include <tydl/Field.hpp>
#include <tydl/Record.hpp>

class Parent;

namespace tydl {

template<class Locator, class Sizer>
class Members<Parent,Locator,Sizer> : public Sizing<Parent,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  union {
    Field<Members,Child,Concrete,Relative<Locator,0>> child1;
    Field<Members,Child,Concrete,Relative<Locator,8>> child2;
    uint8_t bytes_[8+8];
  };
};

} // namespace tydl

class Parent : public tydl::Record<Parent> {
 public:
  using tydl::Record<Parent>::Record;
  using tydl::Record<Parent>::operator=;
  
  ~Parent() {}
  Parent() { memset(this, 0, tydl::num_bytes_allocated_for<Parent>()); }
  Parent(const Parent &other) { set_(other); }
  Parent(Parent &&) = delete;
  Parent &operator=(const Parent &other) { set_(other); return *this; };
  Parent &operator=(Parent &&) = delete;
};

#endif // GENERATED_PARENT_HPP
