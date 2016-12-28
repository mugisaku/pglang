#ifndef PGLANG_TYPE__STRUCT_HPP_INCLUDED
#define PGLANG_TYPE__STRUCT_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"pglang_type__parameter.hpp"
#include"aunique_ptr"




namespace pglang{


struct
StructMember: public Parameter
{
  StructMember(Type&&  type_, std::string&&  name_, Literal&&  lit, size_t  offset);

  size_t  get_tail_offset() const;

};


struct
Struct
{
  size_t            size;
  size_t  alignment_size;

  std::vector<StructMember>  member_list;

  Struct();

  void  append(Type&&  type, std::string&&  name, Literal&&  lit=Literal());

  size_t  get_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




