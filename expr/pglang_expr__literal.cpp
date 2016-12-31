#include"pglang_expr__literal.hpp"
#include"pglang_expr.hpp"
#include"pglang_decl.hpp"
#include<cstdlib>
#include<cinttypes>
#include<new>




namespace pglang{




Literal::Literal(): kind(LiteralKind::null){}
Literal::Literal(nullptr_t  nulptr):         kind(LiteralKind::nullptr_){}
Literal::Literal(bool  b):                   kind(b? LiteralKind::true_:LiteralKind::false_){}
Literal::Literal(int64_t  i):                kind(LiteralKind::integer){data.i = i;}
Literal::Literal(uint64_t  u):               kind(LiteralKind::unsigned_integer){data.u = u;}
Literal::Literal(double  f):                 kind(LiteralKind::floating_point_number){data.f = f;}
Literal::Literal(std::string&&  s):          kind(LiteralKind::string){new(&data.s) std::string(std::move(s));}
Literal::Literal(std::u16string&&  s):       kind(LiteralKind::u16string){new(&data.u16s) std::u16string(std::move(s));}
Literal::Literal(std::u32string&&  s):       kind(LiteralKind::u32string){new(&data.u32s) std::u32string(std::move(s));}


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
  case(LiteralKind::unsigned_integer):
      data.u = rhs.data.u;
      break;
  case(LiteralKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
      new(&data.s) std::string(std::move(rhs.data.s));
      break;
  case(LiteralKind::u16string):
      new(&data.u16s) std::u16string(std::move(rhs.data.u16s));
      break;
  case(LiteralKind::u32string):
      new(&data.u32s) std::u32string(std::move(rhs.data.u32s));
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
  case(LiteralKind::unsigned_integer):
      data.u = rhs.data.u;
      break;
  case(LiteralKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(LiteralKind::string):
      new(&data.s) std::string(rhs.data.s);
      break;
  case(LiteralKind::u16string):
      new(&data.u16s) std::u16string(rhs.data.u16s);
      break;
  case(LiteralKind::u32string):
      new(&data.u32s) std::u32string(rhs.data.u32s);
      break;
    }


  return *this;
}


Literal::operator bool() const{return kind != LiteralKind::null;}


const LiteralData*
Literal::
operator->() const
{
  return &data;
}


LiteralKind
Literal::
get_kind() const
{
  return kind;
}


namespace{
std::vector<Decl*>
tmpdecl_list;
}


Value
Literal::
to_value() const
{
  Value  v;

    switch(kind)
    {
  case(LiteralKind::null):
      break;
  case(LiteralKind::nullptr_):
      v = Value(nullptr);
      break;
  case(LiteralKind::true_):
      v = Value(true);
      break;
  case(LiteralKind::false_):
      v = Value(false);
      break;
  case(LiteralKind::integer):
      v = Value(data.i);
      break;
  case(LiteralKind::unsigned_integer):
      v = Value(data.u);
      break;
  case(LiteralKind::floating_point_number):
      v = Value(data.f);
      break;
  case(LiteralKind::string):
      v = Value(*this);
      break;
  case(LiteralKind::u16string):
      v = Value(*this);
      break;
  case(LiteralKind::u32string):
      v = Value(*this);
      break;
    }


  return std::move(v);
}


Type
Literal::
get_type() const
{
  Decl*  decl = nullptr;

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
  case(LiteralKind::unsigned_integer):
      t = Type(UInt());
      break;
  case(LiteralKind::floating_point_number):
      t = Type(Float());
      break;
  case(LiteralKind::string):
      decl = new Decl(std::string(),Array(Type(Char8()),data.s.size()+1));

      t = Type(*decl);
      break;
  case(LiteralKind::u16string):
      decl = new Decl(std::string(),Array(Char16(),data.u16s.size()+1));

      t = Type(*decl);
      break;
  case(LiteralKind::u32string):
      decl = new Decl(std::string(),Array(Char32(),data.u32s.size()+1));

      t = Type(*decl);
      break;
    }


    if(decl)
    {
      tmpdecl_list.emplace_back(decl);
    }


  return std::move(t);
}


void
Literal::
clear_temporary_declarations()
{
    for(auto  ptr: tmpdecl_list)
    {
      delete ptr;
    }
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
  case(LiteralKind::unsigned_integer):
  case(LiteralKind::floating_point_number):
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
      printf("%" PRId64,data.i);
      break;
  case(LiteralKind::unsigned_integer):
      printf("%" PRIu64,data.u);
      break;
  case(LiteralKind::floating_point_number):
      printf("%f",data.f);
      break;
  case(LiteralKind::string):
      printf("\"%s\"",data.s.data());
      break;
  case(LiteralKind::u16string):
      printf("u16\"");

        for(auto  c: data.u16s)
        {
          printf("0x%X",c);
        }

      printf("\"");
      break;
  case(LiteralKind::u32string):
      printf("u32\"");

        for(auto  c: data.u32s)
        {
          printf("0x%X",c);
        }

      printf("\"");
      break;
    }
}


}




