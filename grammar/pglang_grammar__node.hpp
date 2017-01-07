#ifndef PGLANG_GRAMMAR__NODE_HPP_INCLUDED
#define PGLANG_GRAMMAR__NODE_HPP_INCLUDED


#include<vector>
#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__book.hpp"
#include"pglang_grammar__symbol.hpp"
#include"pglang_parser__token.hpp"


namespace pglang{
namespace grammar{


class
Node
{
  const parser::Token*  token;

  std::vector<Node*>  children;
  
public:
  const Definition&  definition;

  const bool  keyword_flag;

  Node(const Definition&  def, const parser::Token*  tok=nullptr, bool  kw=false);
 ~Node();

  const std::vector<Node*>*  operator->() const;

  size_t  check(const Book&  book);

  void  append(Node*  child);

  void  print() const;

};


}}




#endif




