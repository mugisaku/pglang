#include"pglang_expr__element.hpp"
#include<new>


namespace pglang{


Element::Element():                         kind(ElementKind::null){}
Element::Element(Literal&&  o):             kind(ElementKind::operand){new(&data) Literal(std::move(o));}
Element::Element(const UnaryOperator&  o):  kind(ElementKind::unary_operator){data.operator_ = o;}
Element::Element(const BinaryOperator&  o): kind(ElementKind::binary_operator){data.operator_ = o;}


Element::
Element(const Element&  rhs):
kind(ElementKind::null)
{
  *this = rhs;
}


Element::
Element(Element&&  rhs) noexcept:
kind(ElementKind::null)
{
  *this = std::move(rhs);
}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(const Element&   rhs)
{
  clear();

  kind = rhs.kind;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Literal(rhs.data.operand);
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

    if(kind == ElementKind::operand)
    {
      new(&data.operand) Literal(std::move(rhs.data.operand));
    }

  else
    {
      data.operator_ = rhs.data.operator_;
    }
}


ElementKind
Element::
get_kind() const
{
  return kind;
}


const ElementData*
Element::
operator->() const
{
  return &data;
}


Associativity
Element::
get_associativity() const
{
    if(kind == ElementKind::unary_operator)
    {
        switch(data.operator_)
        {
          case(Operator('!')):
          case(Operator('~')):
          case(Operator('-')): return Associativity::right_to_left;
        }
    }

  else
    {
        switch(data.operator_)
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
    }


  return Associativity::none;
}


Precedence
Element::
get_precedence() const
{
    if(kind == ElementKind::unary_operator)
    {
        switch(data.operator_)
        {
          case(Operator('!')):
          case(Operator('~')):
          case(Operator('-')): return 0x80;
        }
    }

  else
    {
        switch(data.operator_)
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
    }


  return 0;
}


void
Element::
clear()
{
    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.~Literal();
        break;
    }


  kind = ElementKind::null;
}


void
Element::
print(bool  parenthesis) const
{
    if(parenthesis)
    {
      printf("(");
    }


    switch(kind)
    {
      case(ElementKind::operand):
        data.operand.print();
        break;
      case(ElementKind::unary_operator):
      case(ElementKind::binary_operator):
        printf("%s",data.operator_.codes);
        break;
    }


    if(parenthesis)
    {
      printf(")");
    }
}




}




