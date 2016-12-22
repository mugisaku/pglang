#ifndef PGLANG_TYPE__SIGNATURE_HPP_INCLUDED
#define PGLANG_TYPE__SIGNATURE_HPP_INCLUDED


#include"pglang_type__parameter.hpp"
#include<vector>




namespace pglang{


using ParameterList = std::vector<Parameter>;


struct
Signature
{
  Type  return_type;

  ParameterList  parameter_list;

  size_t  get_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




