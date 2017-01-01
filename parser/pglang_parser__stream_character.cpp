#include"pglang_parser__stream.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




std::string
Stream::
get_string_literal()
{
  std::string  s;

    for(;;)
    {
      auto  c = *pointer;

        if(c == '\"')
        {
          ++pointer;

          break;
        }

      else
        if(c == '\\')
        {
          ++pointer;

          auto  uc = get_escchar();

          s.push_back(uc);
        }

      else
        if(iscntrl(c))
        {
          printf("文字列の途中に制御文字が現れました\n");

          throw invalid_string_literal();
        }

      else
        {
          ++pointer;

          s.push_back(c);
        }
    }


  return std::move(s);
}


uint64_t
Stream::
get_character_literal()
{
  uint64_t  c = *pointer++;

    if(c == '\\')
    {
      auto  uc = get_escchar();

      c = uc;
    }


    if(*pointer != '\'')
    {
      throw invalid_character_literal();
    }


  ++pointer;

  return c;
}


char32_t
Stream::
get_escchar()
{
  char32_t  c = *pointer++;

    switch(c)
    {
  case('n'): c = '\n';break;
  case('r'): c = '\r';break;
  case('f'): c = '\f';break;
  case('b'): c = '\b';break;
  case('0'): c = '\0';break;
  case('t'): c = '\t';break;
  case('u'): c = get_unichar16();break;
  case('U'): c = get_unichar32();break;
  default:;
    }


  return c;
}


char16_t
Stream::
get_unichar16()
{
  char16_t  c = 0;

    for(int  n = 0;  n < 4;  ++n)
    {
      int  t;

        if(!get_hexadecimal_number(t))
        {
          printf("error");

          throw invalid_unicode_literal();
        }


      c <<= 4;
      c  |= t;
    }


  return c;
}


char32_t
Stream::
get_unichar32()
{
  char32_t  c = 0;

    for(int  n = 0;  n < 8;  ++n)
    {
      int  t;

        if(!get_hexadecimal_number(t))
        {
          throw invalid_unicode_literal();
        }


      c <<= 4;
      c  |= t;
    }


  return c;
}


}}




