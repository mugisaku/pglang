#ifndef PGLANG_GRAMMAR__SYMBOL_HPP_INCLUDED
#define PGLANG_GRAMMAR__SYMBOL_HPP_INCLUDED


#include<vector>
#include"pglang_parser__token.hpp"
#include"pglang_grammar__group.hpp"


namespace pglang{
namespace grammar{


enum class
SymbolKind
{
  null,

  literal,
  identifier,
  keyword,
  operator_,
  group,
  reference,

  comma,
  semicolon,

};


struct Group;


union
SymbolData
{
  std::string  string;
  Group         group;

  Operator  operator_;

   SymbolData(){};
  ~SymbolData(){};

};


class
Symbol
{
  SymbolKind  kind;
  SymbolData  data;

public:
  Symbol();
  Symbol(std::string&&  s, SymbolKind  k);
  Symbol(Group&&  grp);
  Symbol(Operator&&  op);
  Symbol(parser::Comma&&  comma);
  Symbol(parser::SemiColon&&  semicolon);
  Symbol(      Symbol&&  rhs) noexcept;
  Symbol(const Symbol&   rhs) noexcept;
 ~Symbol();

  Symbol&  operator=(      Symbol&&  rhs) noexcept;
  Symbol&  operator=(const Symbol&   rhs) noexcept;

  const SymbolData*  operator->() const;

  void  clear();

  SymbolKind  get_kind() const;

  void  print() const;

};


}}




#endif




