#include"pglang_scope.hpp"




namespace pglang{




const std::vector<Decl*>*
Scope::
operator->() const
{
  return &decl_table;
}


void
Scope::
append(Decl*  decl)
{
  decl_table.emplace_back(decl);
}


void
Scope::
print() const
{
}


}




