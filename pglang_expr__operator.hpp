#ifndef PGLANG_EXPR__OPERATOR_HPP_INCLUDED
#define PGLANG_EXPR__OPERATOR_HPP_INCLUDED


#include<cstdint>


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


struct
Operator
{
  char  codes[4];


constexpr Operator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
codes{c0,c1,c2,c3}
{}


constexpr operator uint32_t() const
{
  return((codes[0]<<24)|
         (codes[1]<<16)|
         (codes[2]<< 8)|
         (codes[3]    ));
}


};


struct
UnaryOperator: Operator
{
constexpr UnaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
Operator(c0,c1,c2,c3)
{}

  Associativity  get_associativity() const;
  Precedence     get_precedence() const;

};


struct
BinaryOperator: Operator
{
constexpr BinaryOperator(char  c0=0, char  c1=0, char  c2=0, char  c3=0):
Operator(c0,c1,c2,c3)
{}

  Associativity  get_associativity() const;
  Precedence     get_precedence() const;

};


}


#endif




