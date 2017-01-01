#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__element.hpp"




namespace pglang{
namespace grammar{




Definition::
Definition(std::string&&   name_, int  open_, int  close_, Group&&  grp):
name(std::move(name_)),
open(open_),
close(close_),
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
  printf("%s%c%c = ",name.data(),open,close);

  group.print();

  printf(";");
}


}}




