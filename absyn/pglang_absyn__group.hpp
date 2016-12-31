#ifndef PGLANG_ABSYN__GROUP_HPP_INCLUDED
#define PGLANG_ABSYN__GROUP_HPP_INCLUDED


#include<list>
#include"pglang_absyn__element.hpp"


namespace pglang{
namespace absyn{


enum class
GroupKind
{
  null,
  regular,
  repetition,
  option,
};


struct
Separator
{
  char  c;

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




