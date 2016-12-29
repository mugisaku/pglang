#ifndef PGLANG_TYPE__ARRAY_HPP_INCLUDED
#define PGLANG_TYPE__ARRAY_HPP_INCLUDED


#include"pglang_type.hpp"
#include"aunique_ptr"




namespace pglang{


class
Array
{
  Type  type;

  aunique_ptr<size_t>  extent_size;

public:
  Array(Type&&  type_            );
  Array(Type&&  type_, size_t  ex);


  const Type&  get_type() const;

  const size_t*  get_extent_size() const;  

  size_t  get_data_size() const;
  size_t  get_alignment_size() const;

  void  print() const;

};


}


#endif




