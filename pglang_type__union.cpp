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
size(0),
alignment_size(0)
{
}




void
Union::
append(UnionMember&&  member)
{
            size = std::max(          size,member.type.get_size()          );
  alignment_size = std::max(alignment_size,member.type.get_alignment_size());

  member_list.emplace_back(std::move(member));
}


size_t
Union::
get_size() const
{
  return 0;
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
      printf("%s %s;\n",m.type.get_name().data(),m.name.data());
    }
}


}




