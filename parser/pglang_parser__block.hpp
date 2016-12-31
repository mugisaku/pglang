#ifndef PGLANG_PARSER__BLOCK_HPP_INCLUDED
#define PGLANG_PARSER__BLOCK_HPP_INCLUDED


#include<vector>
#include"pglang_expr__operator.hpp"
#include"pglang_parser__token.hpp"


namespace pglang{
namespace parser{


using TokenList = std::vector<Token>;


struct Stream;


class
Block
{
  const int   open_char;
  const int  close_char;

  TokenList  token_list;

public:
  Block(Stream&  s, int  open_c=0, int  close_c=0);

  const TokenList*  operator->() const;

  void  print(int  indent=0) const;

};


}}




#endif




