#include"pglang_type__literal.hpp"
#include<cstdlib>
#include<new>




namespace pglang{




Literal::Literal():                          kind(LiteralKind::null){}
Literal::Literal(int  i):                    kind(LiteralKind::integer){data.i = i;}
Literal::Literal(double  f):                 kind(LiteralKind::fp_number){data.f = f;}
Literal::Literal(std::string&&  s):          kind(LiteralKind::string){new(&data) std::string(std::move(s));}
Literal::Literal(std::vector<Literal>&&  a): kind(LiteralKind::array){new(&data) std::vector<Literal>(std::move(a));}


Literal::
Literal(Literal&&  rhs) noexcept:
kind(LiteralKind::null)
{
  *this = std::move(rhs);
}


Literal::
Literal(const Literal&   rhs):
kind(LiteralKind::null)
{
  *this = rhs;
}


Literal::
~Literal()
{
  clear();
}




Literal&
Literal::
operator=(Literal&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::integer):
      data.i = rhs.data.i;
      break;
  case(LiteralKind::fp_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
      new(&data) std::string(std::move(rhs.data.s));
      break;
  case(LiteralKind::array):
      new(&data) std::vector<Literal>(std::move(rhs.data.a));
      break;
    }


  return *this;
}


Literal&
Literal::
operator=(const Literal&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::integer):
      data.i = rhs.data.i;
      break;
  case(LiteralKind::fp_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
      new(&data) std::string(rhs.data.s);
      break;
  case(LiteralKind::array):
      new(&data) std::vector<Literal>(rhs.data.a);
      break;
    }


  return *this;
}


const LiteralData*
Literal::
operator->() const
{
  return &data;
}


LiteralKind  Literal::get_kind() const{return kind;}


void
Literal::
clear()
{
    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::integer):
      break;
  case(LiteralKind::fp_number):
      break;
  case(LiteralKind::string):
      data.s.~basic_string();
      break;
  case(LiteralKind::array):
      data.a.~vector();
      break;
    }


  kind = LiteralKind::null;
}


}




