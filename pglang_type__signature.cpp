#include"pglang_type__signature.hpp"
#include"pglang_type.hpp"
#include<cstdlib>




namespace pglang{


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




