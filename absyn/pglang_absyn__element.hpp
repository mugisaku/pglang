#ifndef PGLANG_ABSYN__ELEMENT_HPP_INCLUDED
#define PGLANG_ABSYN__ELEMENT_HPP_INCLUDED


#include<vector>
#include"pglang_parser__token.hpp"


namespace pglang{
namespace absyn{


enum class
ElementKind
{
  null,

  literal,
  identifier,
  keyword,
  operator_,
  

};


class
Group
{
  GroupKind  kind;

  Separator  separator;

  ElementList  element_list;

public:

  void  print(int  indent=0) const;

};


}}




#endif




