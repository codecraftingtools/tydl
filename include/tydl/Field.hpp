// Copyright 2021 Jeffrey A. Webb

#ifndef TYDL_FIELD_HPP
#define TYDL_FIELD_HPP

#include <tydl/Sugar.hpp>

namespace tydl {

template<class Parent,
         typename Type,
         template<typename...> typename Representation,
         typename... representation_args>
using Field = Sugar<Parent,Type,Representation<Type,representation_args...>>;

} // namespace tydl

#endif // TYDL_FIELD_HPP
