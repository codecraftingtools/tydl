// Copyright 2021 Jeffrey A. Webb

#ifndef GENERATED_STRUCT2_HPP
#define GENERATED_STRUCT2_HPP

#include <generated/Struct1.hpp>
#include <tydl/Field.hpp>
#include <tydl/Record.hpp>

class Struct2;

namespace tydl {

template<class Locator, class Sizer>
class Members<Struct2,Locator,Sizer> : public Sizing<Struct2,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  union {
    Field<Members,Struct1,Concrete,Relative<Locator,0>> child1;
    Field<Members,Struct1,Concrete,Relative<Locator,6>> child2;
    uint8_t bytes_[6+6];
  };
};

} // namespace tydl

class Struct2 : public tydl::Record<Struct2> {
 public:
  using tydl::Record<Struct2>::Record;
  using tydl::Record<Struct2>::operator=;
  
  ~Struct2() {}
  Struct2() { memset(this, 0, tydl::num_bytes_allocated_for<Struct2>()); }
  Struct2(const Struct2 &other) { set_(other); }
  Struct2(Struct2 &&) = delete;
  Struct2 &operator=(const Struct2 &other) { set_(other); return *this; };
  Struct2 &operator=(Struct2 &&) = delete;
};

#endif // GENERATED_STRUCT2_HPP
