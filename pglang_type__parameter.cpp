#include"pglang_type__parameter.hpp"
#include<cstdlib>




namespace pglang{


Parameter::
Parameter(Type&&  type_, std::string&&  name_, Literal&&  lit):
type(std::move(type_)),
name(std::move(name_)),
literal(std::move(lit)){}


Parameter::
Parameter(std::string&&  name_, Literal&&  lit):
//type(lit.get_default_type()),
name(std::move(name_)),
literal(std::move(lit)){}




void
Parameter::
print() const
{
  printf("%s  %s",type.get_name().data(),name.data());

    if(literal)
    {
      printf("=");

      literal.print();
    }
}


}




