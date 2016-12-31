#ifndef PGLANG_PARSER__TAG_HPP_INCLUDED
#define PGLANG_PARSER__TAG_HPP_INCLUDED


#include<cstddef>


namespace pglang{
namespace parser{


struct
Tag
{
  const char*  base_pointer;
  const char*       pointer;

  size_t   row_number;

  Tag(const char*  p=nullptr):
  base_pointer(p),
  pointer(p),
  row_number(0){}


  void  print() const;

};


}}




#endif




