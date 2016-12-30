#include"pglang_parser__block.hpp"
#include"pglang_parser__stream.hpp"




namespace pglang{
namespace parser{




Block::
Block(Stream&  s, int  open_c, int  close_c):
open_char(open_c),
close_char(close_c)
{
  s.skip_spaces();

    while(s)
    {
        if(*s == close_c)
        {
          s.advance();

          break;
        }


      token_list.emplace_back(s.get_token());
    }
}




const TokenList*
Block::
operator->() const
{
  return &token_list;
}


void
Block::
print() const
{
    if(open_char)
    {
      printf("%c",open_char);
    }


    for(auto&  tok: token_list)
    {
      tok.print();

      printf(" ");
    }


    if(close_char)
    {
      printf("%c",close_char);
    }
}




}}




