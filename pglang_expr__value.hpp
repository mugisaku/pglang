#ifndef PGLANG_EXPR__VALUE_HPP_INCLUDED
#define PGLANG_EXPR__VALUE_HPP_INCLUDED


#include"pglang_type.hpp"




namespace pglang{




struct Literal;


union
ValueData
{
  bool      b;
   int64_t  i;
  uint64_t  u;
  double    f;

  const Literal*  l;

};


class
Value
{
  Type  type;

  ValueData  data;

public:
  Value();
  Value(Type&&  type_        );
  Value(Type&&  type_,  int64_t  i);
  Value(Type&&  type_, uint64_t  u);
  Value(Type&&  type_, double    f);
  Value(nullptr_t  nulptr);
  Value(bool  b);
  Value(int64_t  i);
  Value(uint64_t  u);
  Value(double    f);
  Value(const Literal&  l);
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
  Value  operator[](const Value&  rhs) const;
  Value  operator()(const Value&  rhs) const;

  Value  operator-() const;
  Value  operator~() const;
  Value  operator!() const;
  Value  operator*() const;
  Value  operator&() const;

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




