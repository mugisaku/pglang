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
extent_size(new size_t(ex))
{
}




const Type&  Array::get_type() const{return type;}

const size_t*  Array::get_extent_size() const{return extent_size.get();}

size_t
Array::
get_data_size() const
{
    if(extent_size)
    {
      return type.get_data_size()*(*extent_size);
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

    if(extent_size)
    {
      printf("%d",*extent_size);
    }


  printf("]");
}


}




