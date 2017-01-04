#ifndef PGLANG_GRAMMAR__NODE_HPP_INCLUDED
#define PGLANG_GRAMMAR__NODE_HPP_INCLUDED


#include<vector>
#include"pglang_grammar__definition.hpp"
#include"pglang_parser__token.hpp"


namespace pglang{
namespace grammar{


class
Node
{
  const Definition&  definition;

  const parser::Token*  token;

  std::vector<Node*>  children;
  
public:
  Node(const Definition&  def, const parser::Token*  tok=nullptr);
 ~Node();

  const std::vector<Node*>*  operator->() const;

  void  append(Node*  child);

  void  print() const;

};


}}




#endif




