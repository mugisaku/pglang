#include"pglang_parser__stream.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




Stream::
Stream(const char*  p):
Tag(p)
{
}




Token
Stream::
get_token()
{
  skip_spaces();


  auto  c = *pointer;

    if(!c)
    {
      return Token();
    }


  Tag  tag = *this;

  Token  tok;

    if(ispunct(c))
    {
      tok = Token(tag,get_punctuation_string(),TokenKind::pstring);
    }

  else
    if(isdigit(c))
    {
      uint64_t  i = 0;

        if(c == '0')
        {
          ++pointer;

          auto  next = *pointer;

               if(next == 'x'){  ++pointer;  i = get_hexadecimal_integer_literal();}
          else if(next == 'b'){  ++pointer;  i =      get_binary_integer_literal();}
          else if(next == 'o'){  ++pointer;  i =       get_octet_integer_literal();}
        }

      else
        {
          i = get_decimal_integer_literal();
        }


        if(*pointer == '.')
        {
          char*  endptr;

          auto  d = std::strtod(pointer,&endptr);

            if(pointer == endptr)
            {
              printf("不正な浮動小数数表記です\n");

              throw;
            }


          d += i;

          tok = Token(tag,d);

          pointer = endptr;
        }

      else
        {
          tok = Token(tag,i);
        }
    }

  else
    if(c == '\"')
    {
      ++pointer;

      tok = Token(tag,get_string_literal(),TokenKind::string);
    }

  else
    if(c == '\'')
    {
      ++pointer;

      tok = Token(tag,get_character_literal());
    }

  else
    if((c == 'u') &&
       pointer[1] == '\"')
    {
      pointer += 2;

      tok = Token(tag,get_string_literal(),TokenKind::u16string);
    }

  else
    if((c == 'u') &&
       pointer[1] == '\"')
    {
      pointer += 2;

      tok = Token(tag,get_string_literal(),TokenKind::u32string);
    }

  else
    if(isalpha(c) || (c == '_'))
    {
      auto  id = get_identifier_literal();

           if(id == "nullptr"){tok = Token(tag,NullPtr());}
      else if(id ==    "true"){tok = Token(tag,True());}
      else if(id ==   "false"){tok = Token(tag,False());}
      else {tok = Token(tag,std::move(id),TokenKind::identifier);}
    }


  return std::move(tok);
}




}}




