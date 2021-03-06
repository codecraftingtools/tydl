#ifndef TYDL_FIELD_HPP
#define TYDL_FIELD_HPP

#include <tydl/Accessor.hpp>
#include <cstring> // memcpy

namespace tydl::accessors {

template<typename P, typename T=P, size_t byte_offset=0>
class Field : public Accessor<T,Field<P,T,byte_offset>> {
 public:
  ~Field() {}
  Field() {}
  Field(const Field &f) { (*this)(f()); }
  Field(Field &&) = delete;
  Field &operator=(const Field &f) { (*this)(f()); return *this; };
  Field &operator=(Field &&) = delete;

  Field(const T &t) { (*this)(t); }
  template<typename F2>
  Field(const Accessor<T,F2> &f) { (*this)(f()); }
  
  Field &operator=(const T &t) { (*this)(t); return *this; };
  template<typename F2>
  Field &operator=(const Accessor<T,F2> &a) {
    typedef typename Accessor<T,F2>::Accessor_Subclass_ AA;
    auto &f = *reinterpret_cast<const AA*>(&a);
    (*this)(f());
    return *this;
  };
      
  const T &operator()() const {
    return *reinterpret_cast<const T*>(
        reinterpret_cast<const uint8_t*>(this) + byte_offset);
  }
  
  P &operator()(const T &t) {
    memcpy(reinterpret_cast<uint8_t*>(this) + byte_offset,
           &t, number_of_bytes_in(t));
    return *reinterpret_cast<P*>(this);
  }
  template<typename F2>
  P &operator()(const Accessor<T,F2> &a) {
    typedef typename Accessor<T,F2>::Accessor_Subclass_ AA;
    auto &f = *reinterpret_cast<const AA*>(&a);
    (*this)(f());
    return *reinterpret_cast<P*>(this);
  }
};

} // namespace tydl::accessors

namespace tydl {

template<typename P, typename T=P, size_t byte_offset=0>
class Field : public accessors::Field<P,T,byte_offset> {
 public:
  using accessors::Field<P,T,byte_offset>::Field;
  using accessors::Field<P,T,byte_offset>::operator=;
  
  ~Field() {}
  Field() {}
  Field(const Field &f) { (*this)(f()); }
  Field(Field &&) = delete;
  Field &operator=(const Field &f) { (*this)(f()); return *this; };
  Field &operator=(Field &&) = delete;
};

} // namespace tydl

#endif // TYDL_FIELD_HPP
