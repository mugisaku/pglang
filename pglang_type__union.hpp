#ifndef PGLANG_TYPE__UNION_HPP_INCLUDED
#define PGLANG_TYPE__UNION_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"aunique_ptr"




namespace pglang{


struct
UnionMember
{
  Type  type;

  std::string  name;

  UnionMember(                                   );
  UnionMember(Type&&  type_, std::string&&  name_);

};


struct
Union
{
  std::vector<UnionMember>  member_list;

  size_t            size;
  size_t  alignment_size;

  Union();

  void  append(UnionMember&&  member);

  size_t  get_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




