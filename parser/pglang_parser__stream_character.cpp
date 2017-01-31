#include"pglang_parser__stream.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




uint64_t
Stream::
get_character()
{
  pointer = std::strchr(pointer,'\'')+1;

  uint64_t  c = *pointer++;

    if(c == '\\')
    {
      auto  uc = get_escchar();

      c = uc;
    }


    if(*pointer != '\'')
    {
      throw invalid_character();
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

          throw invalid_unicode();
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
          throw invalid_unicode();
        }


      c <<= 4;
      c  |= t;
    }


  return c;
}


}}




