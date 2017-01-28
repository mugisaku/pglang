#include"pglang_parser__token.hpp"
#include<new>
#include<cinttypes>




namespace pglang{
namespace parser{




Token::Token(): kind(TokenKind::null){}
Token::Token(const Tag&  tag_, uint64_t  i): tag(tag_), kind(TokenKind::integer){data.i = i;}
Token::Token(const Tag&  tag_, double  f):   tag(tag_), kind(TokenKind::floating_point_number){data.f = f;}
Token::Token(const Tag&  tag_, std::string&&  s, TokenKind  k): tag(tag_), kind(k){new(&data.s) std::string(std::move(s));}
Token::Token(const Tag&  tag_, NullPtr&&  n): tag(tag_), kind(TokenKind::nullptr_){}
Token::Token(const Tag&  tag_, True&&  t): tag(tag_), kind(TokenKind::true_){}
Token::Token(const Tag&  tag_, False&&  f): tag(tag_), kind(TokenKind::false_){}
Token::Token(      Token&&  rhs) noexcept: kind(TokenKind::null){*this = std::move(rhs);}
Token::Token(const Token&   rhs)         : kind(TokenKind::null){*this = rhs;}
Token::~Token(){clear();}




Token&
Token::
operator=(Token&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                  ;
         rhs.kind = TokenKind::null;

  tag = rhs.tag;

    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::integer):
      data.i = rhs.data.i;
      break;
  case(TokenKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(TokenKind::string):
  case(TokenKind::identifier):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::pstring):
      new(&data.s) std::string(std::move(rhs.data.s));
      break;
  case(TokenKind::nullptr_):
  case(TokenKind::true_):
  case(TokenKind::false_):
      break;
    }


  return *this;
}


Token&
Token::
operator=(const Token&  rhs)
{
  clear();

  kind = rhs.kind;
   tag = rhs.tag ;

    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::integer):
      data.i = rhs.data.i;
      break;
  case(TokenKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(TokenKind::string):
  case(TokenKind::identifier):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::pstring):
      new(&data.s) std::string(rhs.data.s);
      break;
  case(TokenKind::nullptr_):
  case(TokenKind::true_):
  case(TokenKind::false_):
      break;
    }


  return *this;
}


Token::
operator bool() const
{
  return(kind != TokenKind::null);
}


void
Token::
clear()
{
    switch(kind)
    {
  case(TokenKind::null):
  case(TokenKind::integer):
  case(TokenKind::floating_point_number):
  case(TokenKind::nullptr_):
  case(TokenKind::true_):
  case(TokenKind::false_):
      break;
  case(TokenKind::string):
  case(TokenKind::identifier):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::pstring):
      data.s.~basic_string();
      break;
    }


  kind = TokenKind::null;
}


const TokenData*  Token::operator->() const{return &data;}

TokenKind  Token::get_kind() const{return kind;}


const Tag&  Token::get_tag() const{return tag;}


namespace{
void
prints(const std::string&  s)
{
  printf("\"");

    for(auto  c: s)
    {
        if(iscntrl(c))
        {
          printf("\\");

            switch(c)
            {
          case('\n'): c = 'n';break;
          case('\t'): c = 't';break;
          case('\0'): c = '0';break;
            }
        }


      printf("%c",c);
    }


  printf("\"");
}
}


void
Token::
print() const
{
    switch(kind)
    {
  case(TokenKind::null):
      printf("token(NULL)");
      break;
  case(TokenKind::integer):
      printf("%" PRIu64,data.i);
      break;
  case(TokenKind::floating_point_number):
      printf("%f",data.f);
      break;
  case(TokenKind::string):
      prints(data.s);
      break;
  case(TokenKind::u16string):
      printf("u");
      prints(data.s);
      break;
  case(TokenKind::u32string):
      printf("U");
      prints(data.s);
      break;
  case(TokenKind::identifier):
  case(TokenKind::pstring):
      printf("%s",data.s.data());
      break;
  case(TokenKind::nullptr_):
      printf("nullptr");
      break;
  case(TokenKind::true_):
      printf("true");
      break;
  case(TokenKind::false_):
      printf("false");
      break;
    }
}


}}




