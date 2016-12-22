#ifndef PGLANG_TYPE__LITERAL_HPP_INCLUDED
#define PGLANG_TYPE__LITERAL_HPP_INCLUDED


#include<cstdint>
#include<string>
#include<vector>
#include"pglang_type.hpp"




namespace pglang{




enum class
LiteralKind
{
  null,
  nullptr_,
  true_,
  false_,
  integer,
  fp_number,
  string,
  u16string,
  u32string,
  array,
  identifier,

};


struct Literal;


union
LiteralData
{
  int                   i;
  std::string           s;
  std::u16string        u16s;
  std::u32string        u32s;
  double                f;
  std::vector<Literal>  a;

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
   Literal(int  i);
   Literal(double  f);
   Literal(std::string&&  s);
   Literal(std::u16string&&  u16s);
   Literal(std::u32string&&  u32s);
   Literal(std::vector<Literal>&&  a);
   Literal(      Literal&&  rhs) noexcept;
   Literal(const Literal&   rhs)         ;
  ~Literal();

  Literal&  operator=(      Literal&&  rhs) noexcept;
  Literal&  operator=(const Literal&   rhs)         ;

  const LiteralData*  operator->() const;

  LiteralKind  get_kind() const;

  Type  get_default_type() const;

  void  clear();

  void*  write(void*  ptr) const;

  void  print() const;

};


}


#endif




