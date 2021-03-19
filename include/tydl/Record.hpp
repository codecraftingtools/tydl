#ifndef TYDL_RECORD_HPP
#define TYDL_RECORD_HPP

#include <tydl/Sugar.hpp>
#include <tydl/Concrete.hpp>
#include <tydl/locators.hpp>

namespace tydl {

template<typename Type>
using Record = Sugar<
  Concrete<Type,Beginning>,Type,Concrete<Type,Beginning>>;

} // namespace tydl

#endif // TYDL_RECORD_HPP
