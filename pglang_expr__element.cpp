#include"pglang_expr__element.hpp"
#include"pglang_expr.hpp"
#include<cstdlib>
#include<new>




namespace pglang{




Element::Element():                          kind(ElementKind::null){}
Element::Element(Literal&&  lit):       kind(ElementKind::literal){new(&data) Literal(std::move(lit));}
Element::Element(std::string&&  id):    kind(ElementKind::identifier){new(&data) std::string(std::move(id));}
Element::Element(ArgumentList&&  args): kind(ElementKind::argument_list){new(&data) ArgumentList(std::move(args));}
Element::Element(UnaryOperator  op):    kind(ElementKind::unary_operator){data.unop = op;}
Element::Element(BinaryOperator  op):   kind(ElementKind::binary_operator){data.binop = op;}


Element::
Element(Element&&  rhs) noexcept:
kind(ElementKind::null)
{
  *this = std::move(rhs);
}


Element::
Element(const Element&   rhs):
kind(ElementKind::null)
{
  *this = rhs;
}


Element::
~Element()
{
  clear();
}




Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(ElementKind::null):
      break;
  case(ElementKind::literal):
      new(&data) Literal(std::move(rhs.data.literal));
      break;
  case(ElementKind::identifier):
      new(&data) std::string(std::move(rhs.data.identifier));
      break;
  case(ElementKind::argument_list):
      new(&data) ArgumentList(std::move(rhs.data.args));
      break;
  case(ElementKind::unary_operator):
      data.unop = rhs.data.unop;
      break;
  case(ElementKind::binary_operator):
      data.binop = rhs.data.binop;
      break;
    }


  return *this;
}


Element&
Element::
operator=(const Element&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ElementKind::null):
      break;
  case(ElementKind::literal):
      new(&data) Literal(rhs.data.literal);
      break;
  case(ElementKind::identifier):
      new(&data) std::string(rhs.data.identifier);
      break;
  case(ElementKind::argument_list):
      new(&data) ArgumentList(rhs.data.args);
      break;
  case(ElementKind::unary_operator):
      data.unop = rhs.data.unop;
      break;
  case(ElementKind::binary_operator):
      data.binop = rhs.data.binop;
      break;
    }


  return *this;
}


const ElementData*
Element::
operator->() const
{
  return &data;
}


ElementKind  Element::get_kind() const{return kind;}


Type
Element::
get_type() const
{
  Type  t;

    switch(kind)
    {
  case(ElementKind::null):
      break;
  case(ElementKind::literal):
      t = data.literal.get_type();
      break;
  default:;
    }


  return std::move(t);
}


void
Element::
clear()
{
    switch(kind)
    {
  case(ElementKind::null):
      break;
  case(ElementKind::literal):
      data.literal.~Literal();
      break;
  case(ElementKind::identifier):
      data.identifier.~basic_string();
      break;
  case(ElementKind::argument_list):
      data.args.~vector();
      break;
  default:;
    }


  kind = ElementKind::null;
}


void
Element::
print() const
{
    switch(kind)
    {
  case(ElementKind::null):
      break;
  case(ElementKind::literal):
      data.literal.print();
      break;
  case(ElementKind::identifier):
      printf("%s",data.identifier.data());
      break;
  case(ElementKind::argument_list):
      printf("(");

        for(auto&  l: data.args)
        {
          l.print();
          printf(", ");
        }


      printf(")");
      break;
  case(ElementKind::unary_operator):
  case(ElementKind::binary_operator):
      printf("%s",data.unop.codes);
      break;
    }
}




}




