#ifndef PGLANG_GRAMMAR__GROUP_HPP_INCLUDED
#define PGLANG_GRAMMAR__GROUP_HPP_INCLUDED


#include<vector>


namespace pglang{
namespace grammar{


enum class
GroupKind
{
  regular,
  repetition,
  option,
};


struct
Separator
{
  char  c=0;

};


struct Element;


using ElementList = std::vector<Element>;


class
Group
{
  GroupKind  kind;

  Separator  separator;

  ElementList  element_list;

public:
  Group();

  const ElementList*  operator->() const;

  void  change_separator(char  c);

  const Separator&  get_separator() const;

  void  append(Element&&  e);

  void  change_kind(GroupKind  k);

  GroupKind  get_kind() const;

  void  print() const;

};


}}




#endif




