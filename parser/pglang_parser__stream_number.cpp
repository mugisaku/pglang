#include"pglang_parser__stream.hpp"
#include"pglang_parser__block.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




uint64_t
Stream::
get_binary_integer_literal()
{
  int  i;

    if(!get_binary_number(i))
    {
      printf("文字が一つもありません\n");

      throw;
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
get_octet_integer_literal()
{
  int  i;

    if(!get_octet_number(i))
    {
      printf("文字が一つもありません\n");

      throw;
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
get_decimal_integer_literal()
{
  int  i;

    if(!get_decimal_number(i))
    {
      printf("文字が一つもありません\n");

      throw;
    }


  uint64_t  v = i;

    while(get_decimal_number(i))
    {
      v *= 10;
      v |=  i;
    }


  return v;
}


uint64_t
Stream::
get_hexadecimal_integer_literal()
{
  int  i;

    if(!get_hexadecimal_number(i))
    {
      printf("文字が一つもありません\n");

      throw;
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




