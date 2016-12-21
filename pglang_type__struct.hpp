#ifndef PGLANG_TYPE__STRUCT_HPP_INCLUDED
#define PGLANG_TYPE__STRUCT_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"aunique_ptr"




namespace pglang{


struct
StructMember
{
  Type  type;

  std::string  name;

  size_t  offset;

  StructMember(Type&&  type_, std::string&&  name_, size_t  offset_=0);

  size_t  get_tail_offset() const;

};


struct
Struct
{
  size_t            size;
  size_t  alignment_size;

  std::vector<StructMember>  member_list;

  Struct();

  void  append(Type&&  type, std::string&&  name);

  size_t  get_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


struct
StructDeclaration
{
  std::string  name;

  aunique_ptr<Struct>  definition;

  Book*  book;

  void  print() const
  {
    printf("struct %s{",name.data());

      if(definition){definition->print();}
    else {printf("**UNDEFINED**");}

    printf("}");
  }

};


}


#endif




