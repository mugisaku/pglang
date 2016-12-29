#ifndef PGLANG_TYPE__UNION_HPP_INCLUDED
#define PGLANG_TYPE__UNION_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"aunique_ptr"




namespace pglang{


class
UnionMember
{
  Type  type;

  std::string  name;

public:
  UnionMember(                                   );
  UnionMember(Type&&  type_, std::string&&  name_);

  const Type&  get_type() const{return type;}
  const std::string&  get_name() const{return name;}

};


class
Union
{
  std::vector<UnionMember>  member_list;

  size_t       data_size;
  size_t  alignment_size;

public:
  Union();

  const std::vector<UnionMember>*  operator->() const;

  void  append(Type&&  type, std::string&&  name);

  size_t  get_data_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




