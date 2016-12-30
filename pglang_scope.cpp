#include"pglang_scope.hpp"




namespace pglang{




const std::vector<Decl>*
Scope::
operator->() const
{
  return &decl_table;
}


void
Scope::
append(Decl&&  decl)
{
  decl_table.emplace_back(std::move(decl));
}


Value
Scope::
get_value(const std::string&  name) const
{
    for(auto&  decl: decl_table)
    {
        if(decl.get_name() == name)
        {
            switch(decl.get_kind())
            {
          case(DeclKind::variable):
              break;
          case(DeclKind::constant):
              break;
          case(DeclKind::function):
              break;
            }


          printf("%sは値になりません\n",name.data());

          throw;
        }
    }


    if(parent)
    {
      return parent->get_value(name);
    }


  printf("%sが見つかりません\n",name.data());

  throw;
}


void
Scope::
print() const
{
}


}




