#ifndef PGLANG_EXPR__LITERAL_HPP_INCLUDED
#define PGLANG_EXPR__LITERAL_HPP_INCLUDED


#include<cstdint>
#include<string>
#include<vector>
#include"pglang_expr__value.hpp"




namespace pglang{




struct Expr;
struct Decl;


enum class
LiteralKind
{
  null,

  nullptr_,
  true_,
  false_,
  integer,
  unsigned_integer,
  floating_point_number,
  string,
  u16string,
  u32string,

};


union
LiteralData
{
  int64_t   i;
  uint64_t  u;
  double    f;

  std::string        s;
  std::u16string  u16s;
  std::u32string  u32s;

   LiteralData(){}
  ~LiteralData(){}

};


class
Literal
{
  LiteralKind  kind;
  LiteralData  data;

public:
  Literal();
  Literal(nullptr_t  nulptr);
  Literal(bool  b);
  Literal(int64_t  i);
  Literal(uint64_t  u);
  Literal(double  f);
  Literal(std::string&&  s);
  Literal(std::u16string&&  s);
  Literal(std::u32string&&  s);
  Literal(      Literal&&  rhs) noexcept;
  Literal(const Literal&   rhs);
  ~Literal();

  Literal&  operator=(      Literal&&  rhs) noexcept;
  Literal&  operator=(const Literal&   rhs)         ;

  operator bool() const;

  LiteralKind  get_kind() const;
  const LiteralData*  operator->() const;

  Type  get_type() const;

  Value  to_value() const;

  void  clear();
  void  print() const;

  static void  clear_temporary_declarations();

};


}


#endif




