#ifndef PGLANG_TYPE__SIGNATURE_HPP_INCLUDED
#define PGLANG_TYPE__SIGNATURE_HPP_INCLUDED


#include<memory>
#include<string>
#include<vector>
#include"pglang_type.hpp"




namespace pglang{


struct
Parameter
{
  Type  type;

  std::string  name;

  Parameter(Type&&  type_, std::string&&  name_):
  type(std::move(type_)),
  name(std::move(name_)){}

};


using ParameterList = std::vector<Parameter>;


struct
Signature
{
  Type  return_type;

  ParameterList  parameter_list;

  size_t  get_size() const;
  size_t  get_alignment_size() const;

};


}


#endif




