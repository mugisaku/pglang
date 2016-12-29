#ifndef PGLANG_TYPE__SIGNATURE_HPP_INCLUDED
#define PGLANG_TYPE__SIGNATURE_HPP_INCLUDED


#include"pglang_type__parameter.hpp"
#include<vector>




namespace pglang{


class
Signature
{
  Type  return_type;

  ParameterList  parameter_list;

public:
  Signature(Type&&  type_);

  const ParameterList*  operator->() const;

  const ParameterList&  get_parameter_list() const;

  const Type&  get_return_type() const;

  void  append_parameter(Type&&  type, std::string&&  name, Literal&&  lit=Literal());

  void  print() const;

};


}


#endif




