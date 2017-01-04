#include"pglang_grammar__group.hpp"
#include"pglang_grammar__symbol.hpp"




namespace pglang{
namespace grammar{




Group::
Group():
kind(GroupKind::regular)
{
}




const SymbolList&  Group::operator*() const{return symbol_list;}
const SymbolList*  Group::operator->() const{return &symbol_list;}

void  Group::change_separator(char  c){separator.c = c;}

const Separator&  Group::get_separator() const{return separator;}

void  Group::append(Symbol&&  sym){symbol_list.emplace_back(std::move(sym));}

bool  Group::is_optional() const{return((kind == GroupKind::option) || (kind == GroupKind::repetition));}
bool  Group::is_repetitional() const{return(kind == GroupKind::repetition);}

void  Group::change_kind(GroupKind  k){kind = k;}

GroupKind  Group::get_kind() const{return kind;}


void
Group::
print() const
{
  int   open;
  int  close;

    switch(kind)
    {
  case(GroupKind::regular):
       open = '(';
      close = ')';
      break;
  case(GroupKind::option):
       open = '[';
      close = ']';
      break;
  case(GroupKind::repetition):
       open = '{';
      close = '}';
      break;
    }


  printf("%c",open);

    if(symbol_list.size())
    {
      auto   it = symbol_list.cbegin();
      auto  end = symbol_list.cend();

      it++->print();

        while(it != end)
        {
          printf("%c",separator.c);

          it++->print();
        }
    }


  printf("%c",close);
}


}}




