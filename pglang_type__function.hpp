#ifndef PGLANG_TYPE__FUNCTION_HPP_INCLUDED
#define PGLANG_TYPE__FUNCTION_HPP_INCLUDED


#include"pglang_type__signature.hpp"
#include"pglang_expr__literal.hpp"
#include"pglang_vm__binary.hpp"
#include"aunique_ptr"




namespace pglang{


struct Block;


class
Function
{
  Signature  signature;

  std::vector<Parameter>  vardecl_list;

  size_t  entry_point;

  aunique_ptr<vm::Binary>  binary;
  aunique_ptr<Block>        block;

public:
  Function(Signature&&  sig);

  Literal  execute(const ArgumentList&  args);

  void  declare(Type&&  type,  std::string&&  name, Literal&&  lit=Literal());
  void  declare(std::string&&  name, Literal&&  lit);

  void  print() const;

};


}


#endif




