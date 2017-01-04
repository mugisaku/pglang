#include"pglang_parser__block.hpp"
#include"pglang_parser__stream.hpp"
#include"pglang_parser__token.hpp"
#include"pglang_parser__unicode.hpp"




namespace pglang{
namespace parser{




Block::
Block(Stream&  s, int  begin_c, int  end_c):
beginning_character(begin_c),
ending_character(end_c)
{
  s.skip_spaces();

  Tag  tag;

    try
    {
        while(s)
        {
            if(*s == ending_character)
            {
              s.advance();

              break;
            }


          tag = s;

          token_list.emplace_back(s.get_token());

          s.skip_spaces();
        }
    }


    catch(...)
    {
      tag.print();
    }
}




const TokenList&
Block::
operator*() const
{
  return token_list;
}


const TokenList*
Block::
operator->() const
{
  return &token_list;
}


void
Block::
print(int  indent) const
{
    if(beginning_character)
    {
      printf("%c",beginning_character);
    }


    for(auto&  tok: token_list)
    {
      tok.print(indent);

      printf(" ");
    }


    if(ending_character)
    {
      printf("%c",ending_character);
    }
}




}}




