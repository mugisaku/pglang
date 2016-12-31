#include"pglang_parser__tag.hpp"
#include"pglang_parser__unicode.hpp"




namespace pglang{
namespace parser{


void
Tag::
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


  printf("%4d行,%4d列:\n",row_number+1,col);

  p = base_pointer;

    while(p < pointer)
    {
      fputc(*p++,stdout);
    }


  printf("◇");

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




