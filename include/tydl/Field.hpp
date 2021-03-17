#ifndef TYDL_FIELD_HPP
#define TYDL_FIELD_HPP

#include <tydl/functions.hpp>

namespace tydl {

template<class Parent, class Accessor=Parent>
class Field : public Accessor {
 public:
  using typename Accessor::Type_;
  using Accessor::set_;
  using Accessor::get_;
  
  ~Field() {}
  Field() {}
  Field(const Field &other) { set_(other); }
  Field(Field &&) = delete;
  Field &operator=(const Field &other) { set_(other); return *this; };
  Field &operator=(Field &&) = delete;

  Field(const Type_ &value) { set_(value); }
  template<class Other_Parent, class Other_Accessor>
  Field(const Field<Other_Parent,Other_Accessor> &other) { set_(other); }

  Field &operator=(const Type_ &value) { set_(value); return *this; };
  template<class Other_Parent, class Other_Accessor>
  Field &operator=(const Field<Other_Parent,Other_Accessor> &other) {
    set_(other);
    return *this;
  };
  
  const Type_ &operator()() const { return get_(); }
  
  Parent &operator()(const Type_ &value) {
    set_(value);
    return *reinterpret_cast<Parent*>(this);
  }
  template<class Other_Parent, class Other_Accessor>
  Parent &operator()(const Field<Other_Parent,Other_Accessor> &other) {
    set_(other);
    return *reinterpret_cast<Parent*>(this);
  }
  
  template<class Other_Parent, class Other_Accessor>
  void set_(const Field<Other_Parent,Other_Accessor> &other) {
    set_(other.get_());
  }
};

} // namespace tydl

#endif // TYDL_FIELD_HPP
