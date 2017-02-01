#ifndef PGLANG_PARSER__TOKEN_HPP_INCLUDED
#define PGLANG_PARSER__TOKEN_HPP_INCLUDED


#include<cstddef>
#include<string>
#include"pglang_expr__operator.hpp"
#include"pglang_parser__block.hpp"
#include"pglang_parser__cursor.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


enum class
TokenKind
{
  null,

  tab,
  newline,
  space,
  semicolon,
  character,
  u8character,
  u16character,
  u32character,
  string,
  u8string,
  u16string,
  u32string,

  identifier,

  operator_,
  integer,
  floating_point_number,

  block,

  unknown,

};


union
TokenData
{
  uint64_t  i;
  double  f;

  Block  block;

  std::string  string;

  Operator  operator_;

   TokenData(){}
  ~TokenData(){}

};


class
Token
{
  TokenKind  kind;
  TokenData  data;

  Cursor  cursor;

public:
  Token(TokenKind  k=TokenKind::null);
  Token(uint64_t       i, TokenKind  k);
  Token(std::string&&  s, TokenKind  k);
  Token(double       f);
  Token(Block&&    blk);
  Token(Operator&&  op);
  Token(      Token&&  rhs) noexcept;
  Token(const Token&   rhs) noexcept;
 ~Token(                  );

  Token&  operator=(      Token&&  rhs) noexcept;
  Token&  operator=(const Token&   rhs) noexcept;

  const TokenData&  operator*() const;
  const TokenData*  operator->() const;

  bool  operator==(TokenKind  k) const;

  operator bool() const;

  void  clear();

  void  set_cursor(const Cursor&  cur);
  const Cursor&  get_cursor() const;

  void  print(int  indent) const;

};


}}




#endif




