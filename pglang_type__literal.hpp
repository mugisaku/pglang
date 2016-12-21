#ifndef PGLANG_TYPE__LITERAL_HPP_INCLUDED
#define PGLANG_TYPE__LITERAL_HPP_INCLUDED


#include<cstdint>
#include<string>
#include<vector>




namespace pglang{




enum class
LiteralKind
{
  null,
  integer,
  fp_number,
  string,
  array,

};


struct Literal;


union
LiteralData
{
  int                   i;
  std::string           s;
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
   Literal(int  i);
   Literal(double  f);
   Literal(std::string&&  s);
   Literal(std::vector<Literal>&&  a);
   Literal(      Literal&&  rhs) noexcept;
   Literal(const Literal&   rhs)         ;
  ~Literal();

  Literal&  operator=(      Literal&&  rhs) noexcept;
  Literal&  operator=(const Literal&   rhs)         ;

  const LiteralData*  operator->() const;

  LiteralKind  get_kind() const;

  void  clear();

};


}


#endif




