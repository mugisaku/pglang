#ifndef PGLANG_GRAMMAR__ELEMENT_HPP_INCLUDED
#define PGLANG_GRAMMAR__ELEMENT_HPP_INCLUDED


#include<vector>
#include"pglang_parser__token.hpp"
#include"pglang_grammar__group.hpp"


namespace pglang{
namespace grammar{


enum class
ElementKind
{
  null,

  literal,
  identifier,
  keyword,
  operator_,
  group,
  reference,

};


struct Group;


union
ElementData
{
  std::string  string;
  Group         group;

  Operator  operator_;

   ElementData(){};
  ~ElementData(){};

};


class
Element
{
  ElementKind  kind;
  ElementData  data;

public:
  Element();
  Element(std::string&&  s, ElementKind  k);
  Element(Group&&  grp);
  Element(Operator&&  op);
  Element(      Element&&  rhs) noexcept;
  Element(const Element&   rhs) noexcept;
 ~Element();

  Element&  operator=(      Element&&  rhs) noexcept;
  Element&  operator=(const Element&   rhs) noexcept;

  const ElementData*  operator->() const;

  void  clear();

  ElementKind  get_kind() const;

  void  print() const;

};


}}




#endif




