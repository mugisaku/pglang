#include"pglang_type__literal.hpp"
#include<cstdlib>
#include<new>




namespace pglang{




Literal::Literal():                          kind(LiteralKind::null){}
Literal::Literal(int  i):                    kind(LiteralKind::integer){data.i = i;}
Literal::Literal(double  f):                 kind(LiteralKind::fp_number){data.f = f;}
Literal::Literal(std::string&&  s):          kind(LiteralKind::string){new(&data) std::string(std::move(s));}
Literal::Literal(std::u16string&&  s):       kind(LiteralKind::u16string){new(&data) std::u16string(std::move(s));}
Literal::Literal(std::u32string&&  s):       kind(LiteralKind::u32string){new(&data) std::u32string(std::move(s));}
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
  case(LiteralKind::u16string):
      new(&data) std::u16string(std::move(rhs.data.u16s));
      break;
  case(LiteralKind::u32string):
      new(&data) std::u32string(std::move(rhs.data.u32s));
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
  case(LiteralKind::u16string):
      new(&data) std::u16string(rhs.data.u16s);
      break;
  case(LiteralKind::u32string):
      new(&data) std::u32string(rhs.data.u32s);
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


Type
Literal::
get_default_type() const
{
  Type  t;

    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::integer):
      t = Type(Int());
      break;
  case(LiteralKind::fp_number):
      t = Type(Float32());
      break;
  case(LiteralKind::string):
      t = Type(Array(Char8(),data.s.size()+1));
      break;
  case(LiteralKind::u16string):
      t = Type(Array(Char16(),data.u16s.size()+1));
      break;
  case(LiteralKind::u32string):
      t = Type(Array(Char32(),data.u32s.size()+1));
      break;
  case(LiteralKind::array):
      t = Type(Array(Type(Int()),data.a.size()));
      break;
    }


  return std::move(t);
}


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
  case(LiteralKind::u16string):
      data.u16s.~basic_string();
      break;
  case(LiteralKind::u32string):
      data.u32s.~basic_string();
      break;
  case(LiteralKind::array):
      data.a.~vector();
      break;
    }


  kind = LiteralKind::null;
}


void
Literal::
print() const
{
    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::integer):
      printf("%d",data.i);
      break;
  case(LiteralKind::fp_number):
      printf("%f",data.f);
      break;
  case(LiteralKind::string):
      printf("\"%s\"",data.s.data());
      break;
  case(LiteralKind::u16string):
      printf("u\"");

        for(auto  c: data.u16s)
        {
          printf("0X%02X,",c);
        }


      printf("\"");
      break;
  case(LiteralKind::u32string):
      printf("U\"");

        for(auto  c: data.u32s)
        {
          printf("0X%04X,",c);
        }


      printf("\"");
      break;
  case(LiteralKind::array):
      printf("{");

        for(auto&  lit: data.a)
        {
          lit.print();

          printf(",");
        }


      printf("}");
      break;
    }
}




}




