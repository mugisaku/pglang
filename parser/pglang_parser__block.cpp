#include"pglang_parser__block.hpp"
#include"pglang_parser__token.hpp"
#include"pglang_parser__stream.hpp"




namespace pglang{
namespace parser{




Block::
Block():
opening_c(0),
closing_c(0)
{
}


Block::
Block(const std::string&  s)
{
  Stream  st(s);

  build(st);
}




bool
Block::
build(Stream&  st, char  opening)
{
  clear();

  opening_c = opening;

    switch(opening)
    {
  case('('): closing_c = ')';break;
  case('['): closing_c = ']';break;
  case('{'): closing_c = '}';break;
  case('<'): closing_c = '>';break;
  default:
      closing_c = 0;
    }


    for(;;)
    {
      st.skip_spaces();

      auto  c = *st;

        if((c == ')') ||
           (c == ']') ||
           (c == '}') ||
           (c == '>'))
        {
          st.advance();

          return(c == closing_c);
        }

      else
        if(c == '\0')
        {
          return(c == closing_c);
        }


      emplace_back(st.get_token());
    }
}


void
Block::
print(int  indent) const
{
    if(opening_c)
    {
      printf("%c",opening_c);
    }


    for(auto&  tok: *this)
    {
      tok.print(indent);
    }


    if(closing_c)
    {
      printf("%c",closing_c);
    }
}


}}




