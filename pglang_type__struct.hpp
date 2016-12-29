#ifndef PGLANG_TYPE__STRUCT_HPP_INCLUDED
#define PGLANG_TYPE__STRUCT_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"pglang_type__parameter.hpp"
#include"aunique_ptr"




namespace pglang{


class
Struct
{
  size_t       data_size;
  size_t  alignment_size;

  ParameterList  member_list;

public:
  Struct();

  const ParameterList*  operator->() const;

  void  append(Type&&  type, std::string&&  name, Literal&&  lit=Literal());

  size_t  get_data_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




