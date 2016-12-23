#ifndef PGLANG_TYPE__FUNCTION_HPP_INCLUDED
#define PGLANG_TYPE__FUNCTION_HPP_INCLUDED


#include"pglang_type__signature.hpp"
#include"pglang_expr__literal.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_vm__binary.hpp"
#include"aunique_ptr"




namespace pglang{




struct
Function
{
  Signature  signature;

  std::vector<Parameter>  vardecl_list;

  size_t  entry_point;

  aunique_ptr<vm::Binary>  binary;

  static constexpr size_t  get_size(){return 4;}
  static constexpr size_t  get_alignment_size(){return 4;}

  Literal  execute(const ArgumentList&  args);

  Struct  make_stack_struct() const;
  Struct  make_literaldata_struct() const;

  void  declare(Type&&  type,  std::string&&  name, Literal&&  lit=Literal());
  void  declare(std::string&&  name, Literal&&  lit);

  void  print() const;

};


struct
FunctionDeclaration
{
  std::string  name;

  aunique_ptr<Function>  definition;

  Book*  book;

  void  print() const
  {
    printf("function %s{",name.data());

      if(definition){definition->print();}
    else {printf("**UNDEFINED**");}

    printf("}");
  }

};


}


#endif




