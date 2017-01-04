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


struct Symbol;

using SymbolList = std::vector<Symbol>;


class
Group
{
  GroupKind  kind;

  Separator  separator;

  SymbolList  symbol_list;

public:
  Group();

  const SymbolList&  operator*() const;
  const SymbolList*  operator->() const;

  void  change_separator(char  c);

  const Separator&  get_separator() const;

  bool  is_optional() const;
  bool  is_repetitional() const;

  void  append(Symbol&&  sym);

  void  change_kind(GroupKind  k);

  GroupKind  get_kind() const;


  void  print() const;

};


}}




#endif




