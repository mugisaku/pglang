#include"pglang_expr__operator.hpp"




namespace pglang{


Associativity
UnaryOperator::
get_associativity() const
{
    switch(*this)
    {
      case(Operator('!')):
      case(Operator('~')):
      case(Operator('-')): return Associativity::right_to_left;
    }
}


Associativity
BinaryOperator::
get_associativity() const
{
    switch(*this)
    {
      case(Operator('.')):
      case(Operator('*')):
      case(Operator('/')):
      case(Operator('%')):
      case(Operator('+')):
      case(Operator('-')):
      case(Operator('<','<')):
      case(Operator('>','>')):
      case(Operator('&')):
      case(Operator('|')):
      case(Operator('^')):
      case(Operator('&','&')):
      case(Operator('|','|')): return Associativity::left_to_right;

      case(Operator('<')    ):
      case(Operator('<','=')):
      case(Operator('>')    ):
      case(Operator('>','=')):
      case(Operator('=','=')):
      case(Operator('!','=')): return Associativity::none;

      case(Operator('<','<','=')):
      case(Operator('>','>','=')):
      case(Operator('+','=')):
      case(Operator('-','=')):
      case(Operator('*','=')):
      case(Operator('/','=')):
      case(Operator('%','=')):
      case(Operator('&','=')):
      case(Operator('|','=')):
      case(Operator('^','=')):
      case(Operator('=')    ): return Associativity::right_to_left;

      default:;
    }


  return Associativity::none;
}




Precedence
UnaryOperator::
get_precedence() const
{
    switch(*this)
    {
      case(Operator('!')):
      case(Operator('~')):
      case(Operator('-')): return 0x80;
    }
}


Precedence
BinaryOperator::
get_precedence() const
{
    switch(*this)
    {
      case(Operator('.')): return 0x90;

      case(Operator('*')        ):
      case(Operator('/')        ):
      case(Operator('%')        ): return 0x70;

      case(Operator('+')):
      case(Operator('-')): return 0x60;

      case(Operator('<','<')):
      case(Operator('>','>')): return 0x50;

      case(Operator('<')    ):
      case(Operator('<','=')):
      case(Operator('>')    ):
      case(Operator('>','=')): return 0x40;

      case(Operator('=','=')):
      case(Operator('!','=')): return 0x30;


      case(Operator('&')): return 0x22;
      case(Operator('|')): return 0x21;
      case(Operator('^')): return 0x20;

      case(Operator('&','&')): return 0x11;
      case(Operator('|','|')): return 0x10;

      case(Operator('<','<','=')):
      case(Operator('>','>','=')):
      case(Operator('+','=')):
      case(Operator('-','=')):
      case(Operator('*','=')):
      case(Operator('/','=')):
      case(Operator('%','=')):
      case(Operator('&','=')):
      case(Operator('|','=')):
      case(Operator('^','=')):
      case(Operator('=')    ): return 0x00;

      default:;
    }


  return 0;
}


}




