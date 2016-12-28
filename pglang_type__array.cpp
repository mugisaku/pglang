#include"pglang_type__array.hpp"
#include<cstdlib>




namespace pglang{




Array::
Array(Type&&  type_):
type(std::move(type_))
{
}


Array::
Array(Type&&  type_, size_t  ex):
type(std::move(type_)),
extent(new size_t(ex))
{
}




size_t
Array::
get_size() const
{
    if(extent)
    {
      return type.get_size()*(*extent);
    }


  printf("配列の要素数は定義されていません\n");

  throw;
}


size_t
Array::
get_alignment_size() const
{
  return type.get_alignment_size();
}


void
Array::
print() const
{
  printf("<%s>[",type.get_name().data());

    if(extent)
    {
      printf("%d",*extent);
    }


  printf("]");
}


}




