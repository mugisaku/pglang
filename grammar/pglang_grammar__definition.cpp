#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__symbol.hpp"
#include"pglang_grammar__book.hpp"




namespace pglang{
namespace grammar{




Definition::
Definition(std::string&&   name_, int  begin_, int  end_, Group&&  grp):
name(std::move(name_)),
beginning_character(begin_),
ending_character(end_),
group(std::move(grp))
{
}




const std::string&
Definition::
get_name() const
{
  return name;
}


const Group&
Definition::
get_group() const
{
  return group;
}


void
Definition::
print() const
{
  printf("%s",name.data());

    if(beginning_character)
    {
      printf("%c%c",beginning_character,ending_character);
    }


  printf(" = ");

  group.print();

  printf(";");
}


}}




