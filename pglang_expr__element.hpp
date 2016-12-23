#ifndef PGLANG_EXPR__ELEMENT_HPP_INCLUDED
#define PGLANG_EXPR__ELEMENT_HPP_INCLUDED


#include"pglang_expr__literal.hpp"
#include"pglang_expr__operator.hpp"


namespace pglang{


enum class
Associativity
{
  none,
  left_to_right,
  right_to_left,

};


struct
Precedence
{
  int  number;

  constexpr Precedence(int  n=0): number(n){}

};


enum class
ElementKind
{
  null,
  operand,
  unary_operator,
  binary_operator,

};


union
ElementData
{
  Operator  operator_;

  Literal  operand;

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
  Element(Literal&&  o);
  Element(const UnaryOperator&  o);
  Element(const BinaryOperator&  o);
  Element(const Element&  rhs);
  Element(      Element&&  rhs) noexcept;
  ~Element();


  Element&  operator=(const Element&   rhs)         ;
  Element&  operator=(      Element&&  rhs) noexcept;

  const ElementData*  operator->() const;

  ElementKind  get_kind() const;

  Associativity  get_associativity() const;
  Precedence     get_precedence() const;

  void  clear();

  void  print(bool  parenthesis=false) const;

};


}


#endif




