#ifndef PGLANG_TYPE__FUNCTION_HPP_INCLUDED
#define PGLANG_TYPE__FUNCTION_HPP_INCLUDED


#include"pglang_type__signature.hpp"
#include"pglang_type__literal.hpp"
#include"pglang_vm__binary.hpp"
#include"aunique_ptr"




namespace pglang{




struct
ArgumentList: public std::vector<Literal>
{
  ArgumentList(std::initializer_list<Literal>  ls): std::vector<Literal>(ls){};

};


struct
Function
{
  Signature  signature;

  aunique_ptr<vm::Binary>  binary;

  static constexpr size_t  get_size(){return 4;}
  static constexpr size_t  get_alignment_size(){return 4;}

  Literal  execute(const ArgumentList&  args);

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




