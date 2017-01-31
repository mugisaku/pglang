#include"pglang_parser__stream.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




Token
Stream::
get_number_token()
{
  uint64_t  i = 0;

    if(*pointer == '0')
    {
      ++pointer;

      auto  next = *pointer;

           if(next == 'x' || next == 'X'){  ++pointer;  i = get_hexadecimal_integer();}
      else if(next == 'b' || next == 'B'){  ++pointer;  i =      get_binary_integer();}
      else if(next == 'o' || next == 'O'){  ++pointer;  i =       get_octet_integer();}
    }

  else
    {
      i = get_decimal_integer();
    }


    if(*pointer == '.')
    {
      char*  endptr;

      double  d = std::strtod(pointer,&endptr);

        if(pointer == endptr)
        {
          printf("不正な浮動小数数表記です\n");

          throw;
        }


      pointer = endptr;


      return Token(i+d);
    }


  return Token(i);
}


uint64_t
Stream::
get_binary_integer()
{
  int  i;

    if(!get_binary_number(i))
    {
      throw invalid_number();
    }


  uint64_t  v = i;

    while(get_binary_number(i))
    {
      v <<= 1;
      v  |= i;
    }


  return v;
}


uint64_t
Stream::
get_octet_integer()
{
  int  i;

    if(!get_octet_number(i))
    {
      throw invalid_number();
    }


  uint64_t  v = i;

    while(get_octet_number(i))
    {
      v <<= 3;
      v  |= i;
    }


  return v;
}


uint64_t
Stream::
get_decimal_integer()
{
  int  i;

    if(!get_decimal_number(i))
    {
      throw invalid_number();
    }


  uint64_t  v = i;

    while(get_decimal_number(i))
    {
      v *= 10;
      v +=  i;
    }


  return v;
}


uint64_t
Stream::
get_hexadecimal_integer()
{
  int  i;

    if(!get_hexadecimal_number(i))
    {
      throw invalid_number();
    }


  uint64_t  v = i;

    while(get_hexadecimal_number(i))
    {
      v <<= 4;
      v  |= i;
    }


  return v;
}




bool
Stream::
get_binary_number(int&  i)
{
  auto  c = *pointer;

    if((c >= '0') &&
       (c <= '1'))
    {
      i = c-'0';

      ++pointer;

      return true;
    }


  return false;
}


bool
Stream::
get_octet_number(int&  i)
{
  auto  c = *pointer;

    if((c >= '0') &&
       (c <= '7'))
    {
      i = c-'0';

      ++pointer;

      return true;
    }


  return false;
}


bool
Stream::
get_decimal_number(int&  i)
{
  auto  c = *pointer;

    if((c >= '0') &&
       (c <= '9'))
    {
      i = c-'0';

      ++pointer;

      return true;
    }


  return false;
}


bool
Stream::
get_hexadecimal_number(int&  i)
{
    if(get_decimal_number(i))
    {
      return true;
    }


  auto  c = *pointer;

    if((c >= 'a') &&
       (c <= 'f'))
    {
      i = 10+(c-'a');

      ++pointer;

      return true;
    }

  else
    if((c >= 'A') &&
       (c <= 'B'))
    {
      i = 10+(c-'A');

      ++pointer;

      return true;
    }


  return true;
}


}}




