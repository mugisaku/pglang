#include"pglang_expr__initializer.hpp"
#include"pglang_expr.hpp"
#include"pglang_decl.hpp"
#include<cstdlib>
#include<cinttypes>
#include<new>




namespace pglang{




Initializer::Initializer(): kind(InitializerKind::null){}
Initializer::Initializer(Expr*  expr): kind(InitializerKind::expression){data.expr = expr;}
Initializer::Initializer(InitializerList*  list): kind(InitializerKind::initializer_list){data.list = list;}


Initializer::
Initializer(Initializer&&  rhs) noexcept:
kind(InitializerKind::null)
{
  *this = std::move(rhs);
}


Initializer::
Initializer(const Initializer&   rhs):
kind(InitializerKind::null)
{
  *this = rhs;
}


Initializer::
~Initializer()
{
  clear();
}




Initializer&
Initializer::
operator=(Initializer&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(InitializerKind::null):
      break;
  case(InitializerKind::expression):
      data.expr = rhs.data.expr;
      break;
  case(InitializerKind::initializer_list):
      data.list = rhs.data.list;
      break;
    }


  return *this;
}


Initializer&
Initializer::
operator=(const Initializer&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(InitializerKind::null):
      break;
  case(InitializerKind::expression):
      data.expr = new Expr(*rhs.data.expr);
      break;
  case(InitializerKind::initializer_list):
      data.list = new InitializerList(*rhs.data.list);
      break;
    }


  return *this;
}


Initializer::operator bool() const{return kind != InitializerKind::null;}


const InitializerData*
Initializer::
operator->() const
{
  return &data;
}


InitializerKind
Initializer::
get_kind() const
{
  return kind;
}


void
Initializer::
clear()
{
    switch(kind)
    {
  case(InitializerKind::null):
      break;
  case(InitializerKind::expression):
      delete data.expr;
      break;
  case(InitializerKind::initializer_list):
      delete data.list;
      break;
    }


  kind = InitializerKind::null;
}


void
Initializer::
print() const
{
    switch(kind)
    {
  case(InitializerKind::null):
      break;
  case(InitializerKind::expression):
      printf("(");

      data.expr->print();

      printf(")");
      break;
  case(InitializerKind::initializer_list):
      printf("{");

        for(auto&  e: *data.list)
        {
          e.print();

          printf(",");
        }

      printf("}");
      break;
    }
}


}




