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

class C;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,C,byte_offset> :
    public tydl::Accessor<P,C,byte_offset> {
 public:
  using Accessor<P,C,byte_offset>::operator=;
  using This_ = tydl::Field<P,C,byte_offset>;
  Field() {bzero(this, sizeof(this));}
  union {
    Field<This_,uint32_t,byte_offset+0> c1;
    Field<This_,uint32_t,byte_offset+4> c2;
  };
};

class C : public tydl::Field<C> {};

class D;

template<class P, tydl::size_t byte_offset>
class tydl::Field<P,D,byte_offset> :
    public tydl::Accessor<P,D,byte_offset> {
 public:
  using Accessor<P,D,byte_offset>::operator=;
  using This_ = tydl::Field<P,D,byte_offset>;
  Field() {bzero(this, sizeof(this));}
  union {
    Field<This_,C,byte_offset+0> d1;
    Field<This_,C,byte_offset+8> d2;
  };
};

class D : public tydl::Field<D> {};

int main()
{
  using namespace std;
  
  C c;
  cout << sizeof(c) << endl;
  c.c1(1)
   .c2(2);
  cout << c.c1() << " " << c.c2() << endl;
  
  D d;
  d.d1.c1(3)
      .c2(4)
      .c2(44)
      .c1(33);
  d.d2.c1(5)
      .c2(6);
  d.d2(c);
  cout << d.d1().c1() << " " << d.d1().c2() << endl;
  cout << d.d2().c1() << " " << d.d2().c2() << endl;

  d.d1 = c;
  d.d2.c1 = 5;
  
  // This form works also
  cout << d.d1.c1() << " " << d.d1.c2() << endl;
  cout << d.d2.c1() << " " << d.d2.c2() << endl;

  return 0;
}
