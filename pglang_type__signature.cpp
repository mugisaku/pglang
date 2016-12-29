#include"pglang_type__signature.hpp"
#include"pglang_type.hpp"
#include<cstdlib>




namespace pglang{




Signature::
Signature(Type&&  type_):
return_type(std::move(type_))
{
}




const ParameterList*
Signature::
operator->() const
{
  return &parameter_list;
}


const ParameterList&
Signature::
get_parameter_list() const
{
  return parameter_list;
}


const Type&
Signature::
get_return_type() const
{
  return return_type;
}


void
Signature::
append_parameter(Type&&  type, std::string&&  name, Literal&&  lit)
{
  parameter_list.emplace_back(std::move(type),std::move(name),std::move(lit));
}


void
Signature::
print() const
{
  printf("%s(",return_type.get_name().data());

    for(auto&  p: parameter_list)
    {
      p.print();

      printf(", ");
    }


  printf(")");
}


}




