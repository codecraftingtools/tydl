// Copyright 2021 Jeffrey A. Webb

#ifndef GENERATED_STRUCT1_HPP
#define GENERATED_STRUCT1_HPP

#include <tydl/Field.hpp>
#include <tydl/Record.hpp>

class Struct1;

namespace tydl {

template<class Locator, class Sizer>
class Members<Struct1,Locator,Sizer> : public Sizing<Struct1,Sizer> {
 public:
  ~Members() {}
  Members() {}
  Members(const Members &) = delete;
  Members(Members &&) = delete;
  Members &operator=(const Members &) = delete;
  Members &operator=(Members &&) = delete;

  struct Member2_Sizer_ {
    size_t operator()(const void *ptr) const {
      auto sptr = reinterpret_cast<const Members*>(ptr);
      return sptr->member1.get_();
    }
  };

  struct Member3_Locator_ {
    size_t operator()(const void *ptr) const {
      Locator locator;
      Member2_Sizer_ m2_sizer;
      return locator(ptr) + 1 + m2_sizer(ptr);
    }
  };

  union {
    Field<Members,uint8_t,Concrete,Relative<Locator,0>> member1;
    Field<
      Members,Array<uint8_t,4>,Concrete,Relative<Locator,1>,
      Member2_Sizer_> member2;
    Field<Members,uint8_t,Concrete,Member3_Locator_> member3;
    uint8_t bytes_[1+4+1];
  };
};

} // namespace tydl

class Struct1 : public tydl::Record<Struct1> {
 public:
  using tydl::Record<Struct1>::Record;
  using tydl::Record<Struct1>::operator=;
  
  ~Struct1() {}
  Struct1() { memset(this, 0, tydl::num_bytes_allocated_for<Struct1>()); }
  Struct1(const Struct1 &other) { set_(other); }
  Struct1(Struct1 &&) = delete;
  Struct1 &operator=(const Struct1 &other) { set_(other); return *this; };
  Struct1 &operator=(Struct1 &&) = delete;
};

#endif // GENERATED_STRUCT1_HPP
