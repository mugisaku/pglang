#ifndef PGLANG_PARSER__TOKEN_HPP_INCLUDED
#define PGLANG_PARSER__TOKEN_HPP_INCLUDED


#include<cstdint>
#include<string>
#include"pglang_parser__tag.hpp"


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


union
TokenData
{
  uint64_t  i;
  double    f;

  std::string  s;

  Block*  blk;

   TokenData(){}
  ~TokenData(){}

};


struct SemiColon{};


class
Token
{
  TokenKind  kind;
  TokenData  data;

  Tag  tag;

public:
   Token();
   Token(const Tag&  tag_, uint64_t  i, TokenKind  k);
   Token(const Tag&  tag_, double  f);
   Token(const Tag&  tag_, std::string&&  s, TokenKind  k);
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

  void  print(int  indent=0) const;

};


}}




#endif




