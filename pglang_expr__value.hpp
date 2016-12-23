#ifndef PGLANG_EXPR__VALUE_HPP_INCLUDED
#define PGLANG_EXPR__VALUE_HPP_INCLUDED


#include"pglang_expr__literal.hpp"
#include"pglang_type.hpp"




namespace pglang{




union
ValueData
{
  bool  b;

    int8_t   i8;
   uint8_t  ui8;
   int16_t   i16;
  uint16_t  ui16;
   int32_t   i32;
  uint32_t  ui32;
   int64_t   i64;
  uint64_t  ui64;

  int       i;
  double    f;
  Literal*  l;

};


class
Value
{
  Type  type;

  ValueData  data;

public:
  Value(Type&&  type_         );
  Value(Type&&  type_, const Literal&  l);
  Value(bool  b);
  Value(int  i);
  Value(double  d);
  Value(      Value&&  rhs) noexcept;
  Value(const Value&   rhs);
 ~Value();


  Value&  operator=(      Value&&  rhs) noexcept;
  Value&  operator=(const Value&   rhs);

  const ValueData*  operator->() const;

  Value  operator+(const Value&  rhs) const;
  Value  operator-(const Value&  rhs) const;
  Value  operator*(const Value&  rhs) const;
  Value  operator/(const Value&  rhs) const;
  Value  operator%(const Value&  rhs) const;
  Value  operator==(const Value&  rhs) const;
  Value  operator!=(const Value&  rhs) const;
  Value  operator<(const Value&  rhs) const;
  Value  operator<=(const Value&  rhs) const;
  Value  operator>(const Value&  rhs) const;
  Value  operator>=(const Value&  rhs) const;
  Value  operator<<(const Value&  rhs) const;
  Value  operator>>(const Value&  rhs) const;
  Value  operator&&(const Value&  rhs) const;
  Value  operator||(const Value&  rhs) const;
  Value  operator&(const Value&  rhs) const;
  Value  operator|(const Value&  rhs) const;
  Value  operator^(const Value&  rhs) const;

  Value  operator-() const;
  Value  operator~() const;
  Value  operator!() const;
  Value  operator*() const;

  Value  operator =(const Value&  rhs) const;
  Value  operator+=(const Value&  rhs) const;
  Value  operator-=(const Value&  rhs) const;
  Value  operator*=(const Value&  rhs) const;
  Value  operator/=(const Value&  rhs) const;
  Value  operator%=(const Value&  rhs) const;
  Value  operator<<=(const Value&  rhs) const;
  Value  operator>>=(const Value&  rhs) const;
  Value  operator&=(const Value&  rhs) const;
  Value  operator|=(const Value&  rhs) const;
  Value  operator^=(const Value&  rhs) const;

  Value  to_integer() const;
  Value  to_boolean() const;
  Value  to_floating_point_number() const;

  const Type&  get_type() const;

  void  clear();

  void  print() const;

};


}


#endif




