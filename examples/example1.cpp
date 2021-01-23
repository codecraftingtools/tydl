#include <iostream>
#include <cstdint>
#include <strings.h> // bzero

namespace tydl {

using size_t = uint32_t;

template<class P, class T=P, size_t byte_offset=0>
class Accessor {
 public:
  const T &operator()() const {
    return *reinterpret_cast<const T*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  P &operator()(const T &value) {
    *reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(this) + byte_offset) = value;
    return *reinterpret_cast<P*>(this);
  }
  T operator=(const T &value) {
    *reinterpret_cast<T*>(
        reinterpret_cast<uint8_t*>(this) + byte_offset) = value;
    return value;
  }
};

template<class P, class T=P, size_t byte_offset=0>
class Field : public Accessor<P,T,byte_offset> {
 public:
  using Accessor<P,T,byte_offset>::operator=;
 protected:
  union {
    uint8_t bytes_[sizeof(T) + byte_offset];
  };
};

} // namespace tydl

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

int main()
{
  using namespace std;
  
  Child c;
  cout << sizeof(c) << endl;
  c.member1(1)
   .member2(2);
  cout << c.member1() << " " << c.member2() << endl;
  
  Parent p;
  p.child1.member1(3)
          .member2(4)
          .member2(44)
          .member1(33);
  p.child2.member1(5)
          .member2(6);
  p.child2(c);
  
  cout << p.child1().member1() << " " << p.child1().member2() << endl;
  cout << p.child2().member1() << " " << p.child2().member2() << endl;

  p.child1 = c;
  p.child2.member1 = 5;
  
  // This form works also
  cout << p.child1.member1() << " " << p.child1.member2() << endl;
  cout << p.child2.member1() << " " << p.child2.member2() << endl;

  return 0;
}
