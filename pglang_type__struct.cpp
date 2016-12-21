#include"pglang_type__struct.hpp"
#include"pglang_type.hpp"
#include<cstdlib>




namespace pglang{


StructMember::
StructMember(Type&&  type_, std::string&&  name_, size_t  offset_):
type(std::move(type_)),
name(std::move(name_))
{
  auto  v = type.get_alignment_size();

  offset = ((offset_+v-1)/v*v);
}




size_t
StructMember::
get_tail_offset() const
{
  return offset+type.get_size();
}




Struct::
Struct():
size(0),
alignment_size(0)
{
}




void
Struct::
append(Type&&  type, std::string&&  name)
{
  alignment_size = std::max(alignment_size,type.get_alignment_size());

  size_t  offset = (member_list.size()? member_list.back().get_tail_offset():0);

  member_list.emplace_back(std::move(type),std::move(name),offset);


  auto  tail_offset = member_list.back().get_tail_offset();

  size = (tail_offset+(alignment_size-1))/alignment_size*alignment_size;
}


size_t
Struct::
get_size() const
{
  return size;
}


size_t
Struct::
get_alignment_size() const
{
  return alignment_size;
}




void
Struct::
print() const
{
    for(auto&  m: member_list)
    {
      printf("%s  %s(offset %4d);\n",m.type.get_name().data(),m.name.data(),(int)m.offset);
    }


  printf("size %4d, alignment %4d\n",size,alignment_size);
}


}




