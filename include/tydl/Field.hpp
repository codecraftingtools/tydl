#ifndef TYDL_FIELD_HPP
#define TYDL_FIELD_HPP

#include <tydl/Accessor.hpp>

namespace tydl {

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

#endif // TYDL_FIELD_HPP
