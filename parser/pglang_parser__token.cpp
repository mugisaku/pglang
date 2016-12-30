#include"pglang_parser__token.hpp"
#include"pglang_parser__block.hpp"
#include<new>
#include<cinttypes>




namespace pglang{
namespace parser{




Token::Token(): kind(TokenKind::null){}
Token::Token(const Tag&  tag_, uint64_t  i): tag(tag_), kind(TokenKind::integer){data.i = i;}
Token::Token(const Tag&  tag_, double  f):   tag(tag_), kind(TokenKind::floating_point_number){data.f = f;}
Token::Token(const Tag&  tag_, std::string&&  s, TokenKind  k): tag(tag_), kind(k){new(&data.s) std::string(std::move(s));}
Token::Token(const Tag&  tag_, Operator  op): tag(tag_), kind(TokenKind::operator_){data.op = op;}
Token::Token(const Tag&  tag_, Block*  blk): tag(tag_), kind(TokenKind::block){data.blk = blk;}
Token::Token(const Tag&  tag_, SemiColon&&  semicolon): tag(tag_), kind(TokenKind::semicolon){}
Token::Token(      Token&&  rhs) noexcept: kind(TokenKind::null){*this = std::move(rhs);}
Token::Token(const Token&   rhs)         : kind(TokenKind::null){*this = rhs;}
Token::~Token(){clear();}




Token&
Token::
operator=(Token&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

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
      new(&data.s) std::string(std::move(rhs.data.s));
      break;
  case(TokenKind::operator_):
      data.op = rhs.data.op;
      break;
  case(TokenKind::block):
      data.blk = rhs.data.blk;
      break;
  case(TokenKind::semicolon):
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
      new(&data.s) std::string(rhs.data.s);
      break;
  case(TokenKind::operator_):
      data.op = rhs.data.op;
      break;
  case(TokenKind::block):
      data.blk = new Block(*rhs.data.blk);
      break;
  case(TokenKind::semicolon):
      break;
    }


  return *this;
}


void
Token::
clear()
{
    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::integer):
      break;
  case(TokenKind::floating_point_number):
      break;
  case(TokenKind::string):
  case(TokenKind::identifier):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
      data.s.~basic_string();
      break;
  case(TokenKind::operator_):
      break;
  case(TokenKind::block):
      delete data.blk;
      break;
  case(TokenKind::semicolon):
      break;
    }


  kind = TokenKind::null;
}


const TokenData*  Token::operator->() const{return &data;}

TokenKind  Token::get_kind() const{return kind;}


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
      printf("\"%s\"",data.s.data());
      break;
  case(TokenKind::u16string):
      printf("u\"%s\"",data.s.data());
      break;
  case(TokenKind::u32string):
      printf("U\"%s\"",data.s.data());
      break;
  case(TokenKind::identifier):
      printf("%s",data.s.data());
      break;
  case(TokenKind::operator_):
      printf("%s",data.op.codes);
      break;
  case(TokenKind::block):
      data.blk->print();
      break;
  case(TokenKind::semicolon):
      printf(";");
      break;
    }
}


}}




