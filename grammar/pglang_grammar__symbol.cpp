#include"pglang_grammar__symbol.hpp"
#include"pglang_grammar__group.hpp"
#include<new>




namespace pglang{
namespace grammar{




Symbol::Symbol():kind(SymbolKind::null){}
Symbol::Symbol(std::string&&  s, SymbolKind  k): kind(k){new(&data.string) std::string(std::move(s));}
Symbol::Symbol(Group&&  grp): kind(SymbolKind::group){new(&data.group) Group(std::move(grp));}
Symbol::Symbol(Operator&&  op): kind(SymbolKind::operator_){data.operator_ = op;}
Symbol::Symbol(parser::Comma&&  comma): kind(SymbolKind::comma){}
Symbol::Symbol(parser::SemiColon&&  semicolon): kind(SymbolKind::semicolon){}
Symbol::Symbol(      Symbol&&  rhs) noexcept: kind(SymbolKind::null){*this = std::move(rhs);}
Symbol::Symbol(const Symbol&   rhs) noexcept: kind(SymbolKind::null){*this = rhs;}
Symbol::~Symbol(){clear();}




Symbol&
Symbol::
operator=(Symbol&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = SymbolKind::null;

    switch(kind)
    {
  case(SymbolKind::null):
  case(SymbolKind::literal):
  case(SymbolKind::identifier):
  case(SymbolKind::semicolon):
  case(SymbolKind::comma):
      break;
  case(SymbolKind::keyword):
  case(SymbolKind::reference):
      new(&data.string) std::string(std::move(rhs.data.string));
      break;
  case(SymbolKind::group):
      new(&data.group) Group(std::move(rhs.data.group));
      break;
  case(SymbolKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
    }


  return *this;
}


Symbol&
Symbol::
operator=(const Symbol&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(SymbolKind::null):
  case(SymbolKind::literal):
  case(SymbolKind::identifier):
  case(SymbolKind::semicolon):
  case(SymbolKind::comma):
      break;
  case(SymbolKind::keyword):
  case(SymbolKind::reference):
      new(&data.string) std::string(rhs.data.string);
      break;
  case(SymbolKind::group):
      new(&data.group) Group(rhs.data.group);
      break;
  case(SymbolKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
    }


  return *this;
}


const SymbolData*  Symbol::operator->() const{return &data;}




void
Symbol::
clear()
{
    switch(kind)
    {
  case(SymbolKind::null):
  case(SymbolKind::literal):
  case(SymbolKind::identifier):
  case(SymbolKind::semicolon):
  case(SymbolKind::comma):
      break;
  case(SymbolKind::keyword):
  case(SymbolKind::reference):
      data.string.~basic_string();
      break;
  case(SymbolKind::group):
      data.group.~Group();
      break;
  case(SymbolKind::operator_):
      break;
    }


  kind = SymbolKind::null;
}


SymbolKind  Symbol::get_kind() const{return kind;}


void
Symbol::
print() const
{
    switch(kind)
    {
  case(SymbolKind::literal):    printf("<literal>");break;
  case(SymbolKind::identifier): printf("<identifier>");break;
  case(SymbolKind::keyword):    printf("\"%s\"",data.string.data());break;
  case(SymbolKind::operator_):  printf("\"%s\"",data.operator_.codes);break;
  case(SymbolKind::reference):  printf("%s",data.string.data());break;
  case(SymbolKind::group): data.group.print();break;
  case(SymbolKind::semicolon):  printf("<semicolon>");break;
  case(SymbolKind::comma): printf("<comma>");break;
    }
}


}}




