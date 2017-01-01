#include"pglang_grammar__group.hpp"
#include"pglang_grammar__element.hpp"




namespace pglang{
namespace grammar{




Group::
Group():
kind(GroupKind::regular)
{
}




const ElementList*  Group::operator->() const{return &element_list;}

void  Group::change_separator(char  c){separator.c = c;}

const Separator&  Group::get_separator() const{return separator;}

void  Group::append(Element&&  e){element_list.emplace_back(std::move(e));}

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

    if(element_list.size())
    {
      auto   it = element_list.cbegin();
      auto  end = element_list.cend();

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




