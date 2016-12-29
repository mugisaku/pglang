#include"pglang_type__struct.hpp"
#include"pglang_type.hpp"
#include<cstdlib>




namespace pglang{




Struct::
Struct():
data_size(0),
alignment_size(0)
{
}




const ParameterList*
Struct::
operator->() const
{
  return &member_list;
}


void
Struct::
append(Type&&  type, std::string&&  name, Literal&&  lit)
{
  alignment_size = std::max(alignment_size,type.get_alignment_size());

  size_t  offset = (member_list.size()? member_list.back().get_tail_offset():0);

  member_list.emplace_back(std::move(type),std::move(name),std::move(lit));

  auto&  last = member_list.back();

  last.set_offset(offset);


  auto  tail_offset = last.get_tail_offset();

  data_size = (tail_offset+(alignment_size-1))/alignment_size*alignment_size;
}


size_t
Struct::
get_data_size() const
{
  return data_size;
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
      printf("%s  %s(offset %4d);\n",m.get_type().get_name().data(),m.get_name().data(),(int)m.get_offset());
    }


  printf("data size %4d, alignment size %4d\n",data_size,alignment_size);
}


}




