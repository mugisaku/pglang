#ifndef PGLANG_VM__BINARY_HPP_INCLUDED
#define PGLANG_VM__BINARY_HPP_INCLUDED


#include<cstdint>
#include<vector>
#include"pglang_vm__instruction.hpp"


namespace pglang{
namespace vm{


class
Binary
{
  std::vector<uint8_t>  code_list;

public:
  const std::vector<uint8_t>*  operator->() const;

  void  put(Opecode  opcode);

  void  put_psh8(int  v);
  void  put_psh8u(int  v);
  void  put_psh16(int  v);
  void  put_psh16u(int  v);
  void  put_psh32(int  v);

};


}}




#endif




