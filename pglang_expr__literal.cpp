#include"pglang_expr__literal.hpp"
#include"pglang_expr.hpp"
#include<cstdlib>
#include<new>




namespace pglang{




Literal::Literal():                          kind(LiteralKind::null){}
Literal::Literal(nullptr_t  nulptr):         kind(LiteralKind::nullptr_){}
Literal::Literal(bool  b):                   kind(b? LiteralKind::true_:LiteralKind::false_){}
Literal::Literal(int  i):                    kind(LiteralKind::integer){data.i = i;}
Literal::Literal(double  f):                 kind(LiteralKind::fp_number){data.f = f;}
Literal::Literal(std::string&&  s):          kind(LiteralKind::string){new(&data) std::string(std::move(s));}
Literal::Literal(std::u16string&&  s):       kind(LiteralKind::u16string){new(&data) std::u16string(std::move(s));}
Literal::Literal(std::u32string&&  s):       kind(LiteralKind::u32string){new(&data) std::u32string(std::move(s));}
Literal::Literal(std::vector<Literal>&&  a): kind(LiteralKind::array){new(&data) std::vector<Literal>(std::move(a));}
Literal::Literal(Identifier&&  id):          kind(LiteralKind::identifier){new(&data) std::string(std::move(id.s));}
Literal::Literal(Expr*  expr):               kind(LiteralKind::expression){data.expr = expr;}


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
  case(LiteralKind::nullptr_):
  case(LiteralKind::true_):
  case(LiteralKind::false_):
      break;
  case(LiteralKind::integer):
      data.i = rhs.data.i;
      break;
  case(LiteralKind::fp_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
  case(LiteralKind::identifier):
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
  case(LiteralKind::expression):
      data.expr = rhs.data.expr;
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
  case(LiteralKind::nullptr_):
  case(LiteralKind::true_):
  case(LiteralKind::false_):
      break;
  case(LiteralKind::integer):
      data.i = rhs.data.i;
      break;
  case(LiteralKind::fp_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
  case(LiteralKind::identifier):
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
  case(LiteralKind::expression):
      data.expr = new Expr(*rhs.data.expr);
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
  case(LiteralKind::nullptr_):
      t = Type(NullPtr());
      break;
  case(LiteralKind::true_):
  case(LiteralKind::false_):
      t = Type(Bool());
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
  case(LiteralKind::expression):
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
  case(LiteralKind::nullptr_):
  case(LiteralKind::true_):
  case(LiteralKind::false_):
  case(LiteralKind::integer):
  case(LiteralKind::fp_number):
      break;
  case(LiteralKind::string):
  case(LiteralKind::identifier):
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
  case(LiteralKind::expression):
      delete data.expr;
      break;
    }


  kind = LiteralKind::null;
}


void*
Literal::
write(void*  ptr) const
{
    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::nullptr_):
      break;
  case(LiteralKind::true_):
      break;
  case(LiteralKind::false_):
      break;
  case(LiteralKind::integer):
      break;
  case(LiteralKind::fp_number):
      break;
  case(LiteralKind::string):
    {
      auto  p = static_cast<uint8_t*>(ptr);

        for(auto  c: data.s)
        {
          *p++ = c;
        }


      *p++ = 0;

      ptr = static_cast<void*>(p);
    } break;
  case(LiteralKind::u16string):
    {
      auto  p = static_cast<uint16_t*>(ptr);

        for(auto  c: data.s)
        {
          *p++ = c;
        }


      *p++ = 0;

      ptr = static_cast<void*>(p);
    } break;
  case(LiteralKind::u32string):
    {
      auto  p = static_cast<uint32_t*>(ptr);

        for(auto  c: data.s)
        {
          *p++ = c;
        }


      *p++ = 0;

      ptr = static_cast<void*>(p);
    } break;
  case(LiteralKind::array):
      break;
  case(LiteralKind::expression):
      break;
    }


  return ptr;
}


void
Literal::
print() const
{
    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::nullptr_):
      printf("nullptr");
      break;
  case(LiteralKind::true_):
      printf("true");
      break;
  case(LiteralKind::false_):
      printf("false");
      break;
  case(LiteralKind::integer):
      printf("%d",data.i);
      break;
  case(LiteralKind::fp_number):
      printf("%f",data.f);
      break;
  case(LiteralKind::identifier):
      printf("%s",data.s.data());
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
  case(LiteralKind::expression):
      data.expr->print();
      break;
    }
}




}




