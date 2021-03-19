#ifndef TYDL_SUGAR_HPP
#define TYDL_SUGAR_HPP

namespace tydl {

template<class Parent, typename Type, class Representation>
class Sugar : public Representation {
 public:
  using Representation::set_;
  using Representation::get_;
  
  ~Sugar() {}
  Sugar() {}
  Sugar(const Sugar &other) { set_(other); }
  Sugar(Sugar &&) = delete;
  Sugar &operator=(const Sugar &other) { set_(other); return *this; };
  Sugar &operator=(Sugar &&) = delete;

  Sugar(const Type &value) { set_(value); }
  template<class Other_Parent, class Other_Rep>
  Sugar(const Sugar<Other_Parent,Type,Other_Rep> &other) { set_(other); }

  Sugar &operator=(const Type &value) { set_(value); return *this; };
  template<class Other_Parent, class Other_Rep>
  Sugar &operator=(const Sugar<Other_Parent,Type,Other_Rep> &other) {
    set_(other);
    return *this;
  };
  
  const Type &operator()() const { return get_(); }
  
  Parent &operator()(const Type &value) {
    set_(value);
    return *reinterpret_cast<Parent*>(this);
  }
  template<class Other_Parent, class Other_Rep>
  Parent &operator()(const Sugar<Other_Parent,Type,Other_Rep> &other) {
    set_(other);
    return *reinterpret_cast<Parent*>(this);
  }
  
  template<class Other_Parent, class Other_Rep>
  void set_(const Sugar<Other_Parent,Type,Other_Rep> &other) {
    set_(other.get_());
  }
};

} // namespace tydl

#endif // TYDL_SUGAR_HPP
