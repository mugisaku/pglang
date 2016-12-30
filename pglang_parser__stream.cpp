#include"pglang_parser__stream.hpp"
#include"pglang_parser__block.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




Stream::
Stream(const char*  p):
Tag(p)
{
}




Stream::
operator bool() const
{
  return *pointer;
}


char
Stream::
operator*() const
{
  return *pointer;
}


void
Stream::
advance()
{
  ++pointer;
}


void
Stream::
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
Stream::
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
  else if(*pointer == ','){  pointer += 1;  return Operator(',');}
  else if(*pointer == '.'){  pointer += 1;  return Operator('.');}
  else if(*pointer == ':'){  pointer += 1;  return Operator(':');}
  else if(*pointer == '?'){  pointer += 1;  return Operator('?');}


  printf("不明な演算子です\n");

  throw;
}


namespace{
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
         (c == '.') ||
         (c == ',') ||
         (c == ':'));
}
}


Token
Stream::
get_token()
{
  skip_spaces();


  auto  c = *pointer;

  Tag  tag = *this;

  Token  tok;

    if(isoperator(c))
    {
      tok = Token(tag,get_operator());
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
      tok = Token(tag,get_identifier_literal(),TokenKind::identifier);
    }

  else
    if(c == '(')
    {
      pointer += 1;

      tok = Token(tag,new Block(*this,'(',')'));
    }

  else
    if(c == '{')
    {
      pointer += 1;

      tok = Token(tag,new Block(*this,'{','}'));
    }

  else
    if(c == '[')
    {
      pointer += 1;

      tok = Token(tag,new Block(*this,'[',']'));
    }

  else
    if(c == ';')
    {
      pointer += 1;

      tok = Token(tag,SemiColon());
    }


  return std::move(tok);
}




}}




