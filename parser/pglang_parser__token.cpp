#include"pglang_parser__token.hpp"
#include"pglang_parser__stream.hpp"
#include<cctype>
#include<cstring>
#include<new>




namespace pglang{
namespace parser{




Token::Token(TokenKind  k): kind(k){}
Token::Token(uint64_t       i, TokenKind  k): kind(k){data.i = i;}
Token::Token(std::string&&  s, TokenKind  k): kind(k){new(&data.string) std::string(std::move(s));}
Token::Token(double       f): kind(TokenKind::floating_point_number){data.f = f;}
Token::Token(Block&&    blk): kind(TokenKind::block){new(&data.block) Block(std::move(blk));}
Token::Token(Operator&&  op): kind(TokenKind::operator_){data.operator_ = op;}
Token::Token(      Token&&  rhs) noexcept: kind(TokenKind::null){*this = std::move(rhs);}
Token::Token(const Token&   rhs) noexcept: kind(TokenKind::null){*this = rhs;}
Token::~Token(){clear();}




Token&
Token::
operator=(Token&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

  cursor = rhs.cursor;

    switch(kind)
    {
  case(TokenKind::null):
  case(TokenKind::tab):
  case(TokenKind::newline):
  case(TokenKind::space):
  case(TokenKind::semicolon):
  case(TokenKind::character):
  case(TokenKind::u8character):
  case(TokenKind::u16character):
  case(TokenKind::u32character):
  case(TokenKind::integer):
      data.i = rhs.data.i;
      break;
  case(TokenKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(TokenKind::unknown):
      break;
  case(TokenKind::string):
  case(TokenKind::u8string):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::identifier):
      new(&data.string) std::string(std::move(rhs.data.string));
      break;
  case(TokenKind::block):
      new(&data.block) Block(std::move(rhs.data.block));
      break;
  case(TokenKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
	   }


  return *this;
}


Token&
Token::
operator=(const Token&  rhs) noexcept
{
  clear();

  kind = rhs.kind;
  cursor = rhs.cursor;

    switch(kind)
    {
  case(TokenKind::null):
  case(TokenKind::tab):
  case(TokenKind::newline):
  case(TokenKind::space):
  case(TokenKind::semicolon):
  case(TokenKind::character):
  case(TokenKind::u8character):
  case(TokenKind::u16character):
  case(TokenKind::u32character):
  case(TokenKind::integer):
      data.i = rhs.data.i;
      break;
  case(TokenKind::floating_point_number):
      data.f = rhs.data.f;
      break;
  case(TokenKind::unknown):
      break;
  case(TokenKind::string):
  case(TokenKind::u8string):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::identifier):
      new(&data.string) std::string(rhs.data.string);
      break;
  case(TokenKind::block):
      new(&data.block) Block(rhs.data.block);
      break;
  case(TokenKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
	   }


  return *this;
}


const TokenData&  Token::operator*() const{return data;}
const TokenData*  Token::operator->() const{return &data;}


bool  Token::operator==(TokenKind  k) const{return(kind == k);}

Token::operator bool() const{return(kind != TokenKind::null);}


void
Token::
clear()
{
    switch(kind)
    {
  case(TokenKind::null):
  case(TokenKind::tab):
  case(TokenKind::newline):
  case(TokenKind::space):
  case(TokenKind::semicolon):
  case(TokenKind::character):
  case(TokenKind::u8character):
  case(TokenKind::u16character):
  case(TokenKind::u32character):
  case(TokenKind::integer):
  case(TokenKind::floating_point_number):
  case(TokenKind::operator_):
      break;
  case(TokenKind::unknown):
      break;
  case(TokenKind::string):
  case(TokenKind::u8string):
  case(TokenKind::u16string):
  case(TokenKind::u32string):
  case(TokenKind::identifier):
      data.string.~basic_string();
      break;
  case(TokenKind::block):
      data.block.~Block();
      break;
   }


  kind = TokenKind::null;
}


void
Token::
set_cursor(const Cursor&  cur)
{
  cursor = cur;
}


const Cursor&
Token::
get_cursor() const
{
  return cursor;
}


void
Token::
print(int  indent) const
{
    switch(kind)
    {
  case(TokenKind::null):
      break;
  case(TokenKind::tab):
      Stream::print_character('\t',data.i);
      break;
  case(TokenKind::newline):
      Stream::print_character('\n',data.i);
      break;
  case(TokenKind::space):
      Stream::print_character(' ',data.i);
      break;
  case(TokenKind::semicolon):
      printf(";");
      break;
  case(TokenKind::character):
      Stream::print_character_literal(data.i);
      break;
  case(TokenKind::u8character):
      printf("u8");
      Stream::print_character_literal(data.i);
      break;
  case(TokenKind::u16character):
      printf("u");
      Stream::print_character_literal(data.i);
      break;
  case(TokenKind::u32character):
      printf("U");
      Stream::print_character_literal(data.i);
      break;
  case(TokenKind::integer):
      printf("%llu",data.i);
      break;
  case(TokenKind::floating_point_number):
      printf("%f",data.f);
      break;
  case(TokenKind::operator_):
      printf("%s",data.operator_.codes);
      break;
  case(TokenKind::unknown):
      break;
  case(TokenKind::string):
      Stream::print_string_literal(data.string);
      break;
  case(TokenKind::u8string):
      printf("u8");
      Stream::print_string_literal(data.string);
      break;
  case(TokenKind::u16string):
      printf("u");
      Stream::print_string_literal(data.string);
      break;
  case(TokenKind::u32string):
      printf("U");
      Stream::print_string_literal(data.string);
      break;
  case(TokenKind::identifier):
      printf("%s ",data.string.data());
      break;
  case(TokenKind::block):
      data.block.print(indent+1);
      break;
   }
}


}}




