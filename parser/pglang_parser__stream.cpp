#include"pglang_parser__stream.hpp"
#include"pglang_parser__unicode.hpp"
#include"pglang_parser__block.hpp"
#include<cctype>
#include<cstring>




namespace pglang{
namespace parser{




Stream::
Stream(const std::string&  s):
Cursor(s)
{
}




Token
Stream::
internal__get_whitespace_token()
{
  auto  c = *pointer;

    if((c == '\n') ||
       (c == '\r') ||
       (c == '\t') ||
       (c ==  ' '))
    {
      uint64_t  i = 0;

      const bool  isnl = (c == '\n');

        while(*pointer == c)
        {
          ++pointer;
          ++i;

            if(isnl)
            {
              ++row_number;
            }
        }


        if(isnl)
        {
          base_pointer = pointer;
        }


        switch(c)
        {
      case(' ' ): return Token(i,TokenKind::space);
      case('\n'): return Token(i,TokenKind::newline);
      case('\t'): return Token(i,TokenKind::tab);
      case('\r'): return Token(i,TokenKind::newline);
        }
    }


  return Token();
}


Token
Stream::
internal__get_block_token()
{
  auto  c = *pointer;

    if((c == '(') ||
       (c == '[') ||
       (c == '{'))
    {
      Block  blk;

      ++pointer;

        if(!blk.build(*this,c))
        {
          throw irregular_block();
        }


      return Token(std::move(blk));
    }

  else
    if(c == '<')
    {
      Block  blk;

      auto  cur = *this;

      ++pointer;

        if(blk.build(*this,c))
        {
          return Token(std::move(blk));
        }

      else
        {
          *this = cur;

               if(std::strncmp(pointer,"<<=",3) == 0){  pointer += 3;  return Token(Operator('<','<','='));}
          else if(std::strncmp(pointer,"<<", 2) == 0){  pointer += 2;  return Token(Operator('<','<')    );}
          else                                       {  pointer += 1;  return Token(Operator('<')        );}
        }
    }


  return Token();
}


Token
Stream::
internal__get_nonblock_token()
{
  auto  c = *pointer;

       if(isdigit(c)){return get_number_token();}
  else if(c == '\''){return Token(get_character(),TokenKind::character);}
  else if(c == '\"'){return Token(get_string(),TokenKind::string);}
  else if(c == ';'){  advance();  return Token(TokenKind::semicolon);}
  else if(std::strncmp(pointer,"u8\'",3) == 0){return Token(get_character(),TokenKind::u8character);}
  else if(std::strncmp(pointer,"u8\"",3) == 0){return Token(get_string(),TokenKind::u8string);}
  else if(std::strncmp(pointer,"u\'",2) == 0){return Token(get_character(),TokenKind::u16character);}
  else if(std::strncmp(pointer,"u\"",2) == 0){return Token(get_string(),TokenKind::u16string);}
  else if(std::strncmp(pointer,"U\'",2) == 0){return Token(get_character(),TokenKind::u32character);}
  else if(std::strncmp(pointer,"U\"",2) == 0){return Token(get_string(),TokenKind::u32string);}
  else
    if(isalpha(c) || (c == '_'))
    {
      return Token(get_identifier(),TokenKind::identifier);
    }

  else
    if(ispunct(c))
    {
      return Token(get_operator());
    }

  else
    {
      return Token(TokenKind::unknown);
    }


  return Token();
}


Token
Stream::
get_token()
{
  const Cursor  begin = *this;

  Token  tok;

    if(*pointer)
    {
      tok = internal__get_whitespace_token();

        if(!tok)
        {
          tok = internal__get_block_token();

            if(!tok)
            {
              tok = internal__get_nonblock_token();
            }
        }
    }


  tok.set_cursor(begin);

  return std::move(tok);
}






Operator
Stream::
get_operator()
{
       if(std::strncmp(pointer,"...",3) == 0){  pointer += 3;  return Operator('.','.','.');}
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
  else if(std::strncmp(pointer,">>",2) == 0){  pointer += 2;  return Operator('>','>');}
  else if(std::strncmp(pointer,"&&",2) == 0){  pointer += 2;  return Operator('&','&');}
  else if(std::strncmp(pointer,"||",2) == 0){  pointer += 2;  return Operator('|','|');}
  else if(std::strncmp(pointer,"::",2) == 0){  pointer += 2;  return Operator(':',':');}
  else if(std::strncmp(pointer,"->",2) == 0){  pointer += 2;  return Operator('-','>');}
  else if(std::strncmp(pointer,"##",2) == 0){  pointer += 2;  return Operator('#','#');}
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
  else if(*pointer == '>'){  pointer += 1;  return Operator('>');}
  else if(*pointer == '~'){  pointer += 1;  return Operator('~');}
  else if(*pointer == '.'){  pointer += 1;  return Operator('.');}
  else if(*pointer == ':'){  pointer += 1;  return Operator(':');}
  else if(*pointer == '?'){  pointer += 1;  return Operator('?');}
  else if(*pointer == '#'){  pointer += 1;  return Operator('#');}
  else if(*pointer == ','){  pointer += 1;  return Operator(',');}


  printf("%c 不明な演算子です\n",*pointer);

  throw;
}


std::string
Stream::
get_identifier()
{
  std::string  s;

    while(*pointer)
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


std::string
Stream::
get_string()
{
  std::string  s;

  pointer = std::strchr(pointer,'\"')+1;

    while(*pointer)
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

          throw invalid_string();
        }

      else
        {
          ++pointer;

          s.push_back(c);
        }
    }


  return std::move(s);
}


}}




