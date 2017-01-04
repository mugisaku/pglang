#ifndef PGLANG_PARSER__TOKEN_HPP_INCLUDED
#define PGLANG_PARSER__TOKEN_HPP_INCLUDED


#include<cstdint>
#include<string>
#include"pglang_parser__tag.hpp"
#include"pglang_expr__operator.hpp"
#include"pglang_parser__block.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


enum class
TokenKind
{
  null,

  nullptr_,
  true_,
  false_,
  integer,
  floating_point_number,
  string,
  u16string,
  u32string,
  identifier,
  operator_,
  semicolon,
  comma,

  block,

};


struct Block;


union
TokenData
{
  uint64_t  i;
  double    f;

  std::string  s;

  Operator  operator_;

  Block  blk;

   TokenData(){}
  ~TokenData(){}

};


struct SemiColon{};
struct Comma{};
struct NullPtr{};
struct True{};
struct False{};


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
   Token(const Tag&  tag_, Operator&&  op);
   Token(const Tag&  tag_, std::string&&  s, TokenKind  k);
   Token(const Tag&  tag_, Block&&  blk);
   Token(const Tag&  tag_, SemiColon&&  semicolon);
   Token(const Tag&  tag_, Comma&&  comma);
   Token(const Tag&  tag_, NullPtr&&  n);
   Token(const Tag&  tag_, True&&  t);
   Token(const Tag&  tag_, False&&  f);
   Token(      Token&&  rhs) noexcept;
   Token(const Token&   rhs)         ;
  ~Token();

  Token&  operator=(      Token&&  rhs) noexcept;
  Token&  operator=(const Token&   rhs)         ;

  void  clear();

  const TokenData*  operator->() const;

  TokenKind  get_kind() const;

  const Tag&  get_tag() const;

  void  print(int  indent=0) const;

};


}}




#endif




