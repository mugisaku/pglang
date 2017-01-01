#include"pglang_parser__tag.hpp"
#include"pglang_parser__unicode.hpp"
#include<cstring>




namespace pglang{
namespace parser{




Tag::
Tag(const char*  p):
base_pointer(p),
pointer(p),
row_number(0)
{
}




Tag::
operator bool() const
{
  return *pointer;
}


char
Tag::
operator*() const
{
  return *pointer;
}


void
Tag::
advance()
{
  ++pointer;
}


void
Tag::
skip_spaces()
{
    for(;;)
    {
      auto  c = *pointer;

        if(isspace(c))
        {
          pointer += 1;

            if(c == '\n')
            {
              base_pointer = pointer;

              row_number += 1;
            }
        }

      else
        {
          break;
        }
    }
}


Operator
Tag::
get_operator()
{
       if(std::strncmp(pointer,"...",3) == 0){  pointer += 3;  return Operator('.','.','.');}
  else if(std::strncmp(pointer,"<<=",3) == 0){  pointer += 3;  return Operator('<','<','=');}
  else if(std::strncmp(pointer,">>=",3) == 0){  pointer += 3;  return Operator('>','>','=');}
  else if(std::strncmp(pointer,"+=",2) == 0){  pointer += 2;  return Operator('+','=');}
  else if(std::strncmp(pointer,"++",2) == 0){  pointer += 2;  return Operator('+','+');}
  else if(std::strncmp(pointer,"-=",2) == 0){  pointer += 2;  return Operator('-','=');}
  else if(std::strncmp(pointer,"--",2) == 0){  pointer += 2;  return Operator('-','-');}
  else if(std::strncmp(pointer,"*=",2) == 0){  pointer += 2;  return Operator('*','=');}
  else if(std::strncmp(pointer,"/=",2) == 0){  pointer += 2;  return Operator('/','=');}
  else if(std::strncmp(pointer,"%=",2) == 0){  pointer += 2;  return Operator('%','=');}
  else if(std::strncmp(pointer,"|=",2) == 0){  pointer += 2;  return Operator('|','=');}
  else if(std::strncmp(pointer,"&=",2) == 0){  pointer += 2;  return Operator('&','=');}
  else if(std::strncmp(pointer,"^=",2) == 0){  pointer += 2;  return Operator('^','=');}
  else if(std::strncmp(pointer,"==",2) == 0){  pointer += 2;  return Operator('=','=');}
  else if(std::strncmp(pointer,"!=",2) == 0){  pointer += 2;  return Operator('!','=');}
  else if(std::strncmp(pointer,"<=",2) == 0){  pointer += 2;  return Operator('<','=');}
  else if(std::strncmp(pointer,">=",2) == 0){  pointer += 2;  return Operator('>','=');}
  else if(std::strncmp(pointer,"<<",2) == 0){  pointer += 2;  return Operator('<','<');}
  else if(std::strncmp(pointer,">>",2) == 0){  pointer += 2;  return Operator('>','>');}
  else if(std::strncmp(pointer,"&&",2) == 0){  pointer += 2;  return Operator('&','&');}
  else if(std::strncmp(pointer,"||",2) == 0){  pointer += 2;  return Operator('|','|');}
  else if(std::strncmp(pointer,"::",2) == 0){  pointer += 2;  return Operator(':',':');}
  else if(std::strncmp(pointer,"->",2) == 0){  pointer += 2;  return Operator('-','>');}
  else if(*pointer == '+'){  pointer += 1;  return Operator('+');}
  else if(*pointer == '-'){  pointer += 1;  return Operator('-');}
  else if(*pointer == '*'){  pointer += 1;  return Operator('*');}
  else if(*pointer == '/'){  pointer += 1;  return Operator('/');}
  else if(*pointer == '%'){  pointer += 1;  return Operator('%');}
  else if(*pointer == '|'){  pointer += 1;  return Operator('|');}
  else if(*pointer == '&'){  pointer += 1;  return Operator('&');}
  else if(*pointer == '^'){  pointer += 1;  return Operator('^');}
  else if(*pointer == '!'){  pointer += 1;  return Operator('!');}
  else if(*pointer == '='){  pointer += 1;  return Operator('=');}
  else if(*pointer == '<'){  pointer += 1;  return Operator('<');}
  else if(*pointer == '>'){  pointer += 1;  return Operator('>');}
  else if(*pointer == '~'){  pointer += 1;  return Operator('~');}
  else if(*pointer == '.'){  pointer += 1;  return Operator('.');}
  else if(*pointer == ':'){  pointer += 1;  return Operator(':');}
  else if(*pointer == '?'){  pointer += 1;  return Operator('?');}


  printf("不明な演算子です\n");

  throw;
}


std::string
Tag::
get_identifier_literal()
{
  std::string  s;

  s.push_back(*pointer++);

    for(;;)
    {
      auto  c = *pointer;

        if(isalnum(c) || (c == '_'))
        {
          ++pointer;

          s.push_back(c);
        }

      else
        {
          break;
        }
    }


  return std::move(s);
}


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




bool
isoperator(int  c)
{
  return((c == '+') ||
         (c == '-') ||
         (c == '*') ||
         (c == '/') ||
         (c == '%') ||
         (c == '!') ||
         (c == '<') ||
         (c == '>') ||
         (c == '=') ||
         (c == '&') ||
         (c == '|') ||
         (c == '^') ||
         (c == '~') ||
         (c == '?') ||
         (c == '#') ||
         (c == '.') ||
         (c == ':'));
}


}}




