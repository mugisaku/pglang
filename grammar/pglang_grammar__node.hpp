#ifndef PGLANG_GRAMMAR__NODE_HPP_INCLUDED
#define PGLANG_GRAMMAR__NODE_HPP_INCLUDED


#include<vector>
#include"pglang_parser__token.hpp"
#include"pglang_grammar__element.hpp"


namespace pglang{
namespace grammar{


class
Node
{

public:
  Node();

  void  print() const;

};


}}




#endif




