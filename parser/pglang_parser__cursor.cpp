#include"pglang_parser__cursor.hpp"
#include"pglang_parser__unicode.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




Cursor::
Cursor():
base_pointer(nullptr),
pointer(nullptr),
row_number(0)
{
}


Cursor::
Cursor(const std::string&  s):
base_pointer(s.data()),
pointer(s.data()),
row_number(0)
{
}




char
Cursor::
operator*() const
{
  return *pointer;
}


void
Cursor::
advance()
{
    if(pointer)
    {
      ++pointer;
    }
}


void
Cursor::
newline()
{
  base_pointer = pointer;

  row_number += 1;
}


void
Cursor::
skip_spaces()
{
    while(*pointer)
    {
      auto  c = *pointer;

        if((c ==  ' ') ||
           (c == '\t') ||
           (c == '\r'))
        {
          pointer += 1;
        }

      else
        {
          break;
        }
    }
}


namespace{
void
printc(int  c)
{
    switch(c)
    {
  case('\n'): printf("\\n");break;
  case('\0'): printf("\\0");break;
  case('\t'): printf("\\t");break;
  case('\r'): printf("\\r");break;
  case('\\'): printf("\\\\");break;
  case('\"'): printf("\\\"");break;
  case('\''): printf("\\\'");break;
  default: printf("%c",c);
    }
}
}

void
Cursor::
print_character(int  c)
{
  printf("\'");

  printc(c);

  printf("\'");
}


void
Cursor::
print_string(const std::string&  s)
{
  auto  begin = s.cbegin();
  auto    end = s.cend();

  printf("\"");

    while(begin != end)
    {
      printc(*begin++);
    }


  printf("\"");
}


void
Cursor::
print() const
{
  int  col = 1;

  auto  p = base_pointer;

    while(p < pointer)
    {
      auto  n = get_utf8_byte_number(*p);

      col += 1;
        p += n;
    }


  printf("[%4d行,%4d列]: ",row_number+1,col);

  p = base_pointer;

    while(p < pointer)
    {
      fputc(*p++,stdout);
    }


  printf("■");

    while(*p)
    {
        if(*p == '\n')
        {
          break;
        }


      fputc(*p++,stdout);
    }
}


}}




