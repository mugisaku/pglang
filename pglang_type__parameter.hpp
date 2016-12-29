#ifndef PGLANG_TYPE__PARAMETER_HPP_INCLUDED
#define PGLANG_TYPE__PARAMETER_HPP_INCLUDED


#include<string>
#include<vector>
#include"pglang_type.hpp"
#include"pglang_expr__literal.hpp"




namespace pglang{


class
Parameter
{
  Type  type;

  std::string  name;

  Literal  literal;

  size_t  offset;

public:
  Parameter(Type&&  type_, std::string&&  name_, Literal&&  lit=Literal());
  Parameter(               std::string&&  name_, Literal&&  lit          );

  const Type&  get_type() const;

  const std::string&  get_name() const;

  const Literal&  get_literal() const;

  void  set_offset(size_t  v);

  size_t  get_offset() const;

  size_t  get_tail_offset() const;

  void  print() const;

};


struct Variable: public Parameter{using Parameter::Parameter;};
struct Constant: public Parameter{using Parameter::Parameter;};


using ParameterList = std::vector<Parameter>;


}


#endif




