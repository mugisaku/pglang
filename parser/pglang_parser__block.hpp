#ifndef PGLANG_PARSER__BLOCK_HPP_INCLUDED
#define PGLANG_PARSER__BLOCK_HPP_INCLUDED


#include<vector>
#include"pglang_expr__operator.hpp"


namespace pglang{
namespace parser{


struct Token;


using TokenList = std::vector<Token>;


struct Stream;


class
Block
{
  TokenList  token_list;

public:
  const int  beginning_character;
  const int     ending_character;

  Block(Stream&  s, int  begin_c=0, int  end_c=0);

  const TokenList&  operator*() const;
  const TokenList*  operator->() const;

  void  print(int  indent=0) const;

};


}}




#endif




