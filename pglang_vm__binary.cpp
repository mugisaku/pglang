#include"pglang_vm__binary.hpp"
#include<cstring>
#include<utility>




namespace pglang{
namespace vm{




const std::vector<uint8_t>*
Binary::
operator->() const
{
  return &code_list;
}


void
Binary::
put(Opecode  opcode)
{
  code_list.push_back(static_cast<int>(opcode));
}


void
Binary::
put_psh8(int  v)
{
  code_list.push_back(static_cast<int>(Opecode::psh8));
  code_list.push_back(v);
}


void
Binary::
put_psh8u(int  v)
{
  code_list.push_back(static_cast<int>(Opecode::psh8u));
  code_list.push_back(v);
}


void
Binary::
put_psh16(int  v)
{
  code_list.push_back(static_cast<int>(Opecode::psh16));
  code_list.push_back(v>>8);
  code_list.push_back(v);
}


void
Binary::
put_psh16u(int  v)
{
  code_list.push_back(static_cast<int>(Opecode::psh16u));
  code_list.push_back(v>>8);
  code_list.push_back(v);
}


void
Binary::
put_psh32(int  v)
{
  code_list.push_back(static_cast<int>(Opecode::psh32));
  code_list.push_back(v>>24);
  code_list.push_back(v>>16);
  code_list.push_back(v>> 8);
  code_list.push_back(v    );
}



}}




