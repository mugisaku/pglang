#ifndef PGLANG_EXPR__ELEMENT_HPP_INCLUDED
#define PGLANG_EXPR__ELEMENT_HPP_INCLUDED


#include<cstdint>
#include<string>
#include<vector>
#include<utility>
#include"pglang_type.hpp"
#include"pglang_expr__literal.hpp"
#include"pglang_expr__operator.hpp"




namespace pglang{




struct Expr;


struct
ArrayLiteral: public std::vector<Literal>
{
};

struct
ArgumentList: public ArrayLiteral
{
};


enum class
ElementKind
{
  null,

  literal,

  identifier,
  argument_list,
  unary_operator,
  binary_operator,

};


union
ElementData
{
  Literal         literal;
  std::string  identifier;

  ArgumentList     args;
   UnaryOperator   unop;
  BinaryOperator  binop;

   ElementData(){}
  ~ElementData(){}

};


class
Element
{
  ElementKind  kind;
  ElementData  data;

public:
   Element();
   Element(Literal&&  lit);
   Element(std::string&&  id);
   Element(ArgumentList&&  args);
   Element(UnaryOperator  op);
   Element(BinaryOperator  op);
   Element(      Element&&  rhs) noexcept;
   Element(const Element&   rhs)         ;
  ~Element();

  Element&  operator=(      Element&&  rhs) noexcept;
  Element&  operator=(const Element&   rhs)         ;

  const ElementData*  operator->() const;

  ElementKind  get_kind() const;

  Type  get_type() const;

  void  clear();

  void  print() const;

};


}


#endif




