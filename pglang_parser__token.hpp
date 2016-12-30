#ifndef PGLANG_PARSER__TOKEN_HPP_INCLUDED
#define PGLANG_PARSER__TOKEN_HPP_INCLUDED


#include<cstdint>
#include<string>
#include"pglang_expr__operator.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


enum class
TokenKind
{
  null,

  integer,
  floating_point_number,
  string,
  u16string,
  u32string,
  identifier,
  operator_,
  semicolon,

  block,

};


struct Block;


struct
TokenData
{
  uint64_t  i;
  double    f;

  std::string  s;

  Operator  op;

  Block*  blk;

   TokenData(){}
  ~TokenData(){}

};


struct SemiColon{};


struct
Tag
{
  const char*  base_pointer;
  const char*       pointer;

  size_t   row_number;

  Tag(const char*  p=nullptr):
  base_pointer(p),
  pointer(p),
  row_number(0){}

};


class
Token
{
  TokenKind  kind;
  TokenData  data;

  Tag  tag;

public:
   Token();
   Token(const Tag&  tag_, uint64_t  i);
   Token(const Tag&  tag_, double  f);
   Token(const Tag&  tag_, std::string&&  s, TokenKind  k);
   Token(const Tag&  tag_, Operator  op);
   Token(const Tag&  tag_, Block*  blk);
   Token(const Tag&  tag_, SemiColon&&  semicolon);
   Token(      Token&&  rhs) noexcept;
   Token(const Token&   rhs)         ;
  ~Token();

  Token&  operator=(      Token&&  rhs) noexcept;
  Token&  operator=(const Token&   rhs)         ;

  void  clear();

  const TokenData*  operator->() const;

  TokenKind  get_kind() const;

  void  print() const;

};


}}




#endif




