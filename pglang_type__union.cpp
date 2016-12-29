#include"pglang_type__union.hpp"
#include"pglang_type.hpp"
#include<cstdlib>




namespace pglang{


UnionMember::
UnionMember()
{
}


UnionMember::
UnionMember(Type&&  type_, std::string&&  name_):
type(std::move(type_)),
name(std::move(name_))
{
}




Union::
Union():
data_size(0),
alignment_size(0)
{
}




const std::vector<UnionMember>*
Union::
operator->() const
{
  return &member_list;
}


void
Union::
append(Type&&  type, std::string&&  name)
{
       data_size = std::max(     data_size,type.get_data_size()     );
  alignment_size = std::max(alignment_size,type.get_alignment_size());

  member_list.emplace_back(std::move(type),std::move(name));
}


size_t
Union::
get_data_size() const
{
  return data_size;
}


size_t
Union::
get_alignment_size() const
{
  return alignment_size;
}


void
Union::
print() const
{
    for(auto&  m: member_list)
    {
      printf("%s %s;\n",m.get_type().get_name().data(),m.get_name().data());
    }
}


}




