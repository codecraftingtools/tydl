#ifndef GENERATED_CHILD_HPP
#define GENERATED_CHILD_HPP

#include <tydl/Field.hpp>
#include <tydl/Record.hpp>

class Child;

namespace tydl {
template<class Locator, class Sizer>
class Members<Child,Locator,Sizer> : public Sizing<Child,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  union {
    Field<Members,uint32_t,Concrete,Relative<Locator,0>> member1;
    Field<Members,uint32_t,Concrete,Relative<Locator,4>> member2;
    uint8_t bytes_[4+4];
  };
};

} // namespace tydl

class Child : public tydl::Record<Child> {
 public:
  using tydl::Record<Child>::Record;
  using tydl::Record<Child>::operator=;
  
  ~Child() {}
  Child() { memset(this, 0, tydl::num_bytes_allocated_for<Child>()); }
  Child(const Child &other) { set_(other); }
  Child(Child &&) = delete;
  Child &operator=(const Child &other) { set_(other); return *this; };
  Child &operator=(Child &&) = delete;
};

#endif // GENERATED_CHILD_HPP
