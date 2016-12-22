#ifndef PGLANG_TYPE__PARAMETER_HPP_INCLUDED
#define PGLANG_TYPE__PARAMETER_HPP_INCLUDED


#include<string>
#include"pglang_type.hpp"
#include"pglang_type__literal.hpp"




namespace pglang{


struct
Parameter
{
  Type  type;

  std::string  name;

  Literal  literal;

  size_t  offset;

  Parameter(Type&&  type_, std::string&&  name_, Literal&&  lit=Literal());
  Parameter(               std::string&&  name_, Literal&&  lit          );

  void  print() const;

};


}


#endif




