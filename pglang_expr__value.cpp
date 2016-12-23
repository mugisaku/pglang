#include"pglang_expr__value.hpp"
#include"pglang_type.hpp"
#include<new>




namespace pglang{




Value::Value(Type&&  type_): type(std::move(type_)){}
Value::Value(Type&&  type_, const Literal&  l): type(std::move(type_)){data.l = new Literal(l);}
Value::Value(bool  b):    type(Bool()){data.i = b;}
Value::Value(int  i):    type(Int()){data.i = i;}
Value::Value(double  f): type(Float()){data.f = f;}
Value::Value(      Value&&  rhs) noexcept{*this = std::move(rhs);}
Value::Value(const Value&   rhs){*this = rhs;}
Value::~Value(){clear();}



Value&
Value::
operator=(Value&&  rhs) noexcept
{
  clear();

  type = std::move(rhs.type);
  data = rhs.data;

  return *this;
}


Value&
Value::
operator=(const Value&   rhs)
{
  clear();

  type = rhs.type;

    if(type == TypeKind::literal)
    {
      data.l = new Literal(*rhs.data.l);
    }

  else
    {
      data = rhs.data;
    }
}


void
Value::
clear()
{
    if(type == TypeKind::literal)
    {
      delete data.l;
    }


  type = Type();
}


const Type&
Value::
get_type() const
{
  return type;
}


const ValueData*  Value::operator->() const{return &data;}


Value
Value::
operator+(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i+b->i);
    }


    catch(...)
    {
      printf("%sは加算できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator-(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i-b->i);
    }


    catch(...)
    {
      printf("%sは減算できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator*(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i*b->i);
    }


    catch(...)
    {
      printf("%sは乗算できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator/(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

        if(!b->i)
        {
          printf("ゼロ除算が起きました\n");

          throw;
        }


      return Value(a->i/b->i);
    }


    catch(...)
    {
      printf("%sは除算できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator%(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

        if(!b->i)
        {
          printf("ゼロ除算が起きました\n");

          throw;
        }


      return Value(a->i%b->i);
    }


    catch(...)
    {
      printf("%sは剰余できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator==(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i == b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator!=(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i != b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator<(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i < b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator<=(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i <= b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator>(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i > b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator>=(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i >= b->i);
    }


    catch(...)
    {
      printf("%sは比較できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator<<(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i<<b->i);
    }


    catch(...)
    {
      printf("%sは左シフトできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator>>(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i>>b->i);
    }


    catch(...)
    {
      printf("%sは右シフトできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator&&(const Value&  rhs) const
{
    try
    {
      auto  a =     to_boolean();
      auto  b = rhs.to_boolean();

      return Value(a->b&&b->b);
    }


    catch(...)
    {
      printf("%sは論値ANDできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator||(const Value&  rhs) const
{
    try
    {
      auto  a =     to_boolean();
      auto  b = rhs.to_boolean();

      return Value(a->b||b->b);
    }


    catch(...)
    {
      printf("%sは論値ORできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator&(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i|b->i);
    }


    catch(...)
    {
      printf("%sはビットANDできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator|(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i|b->i);
    }


    catch(...)
    {
      printf("%sはビットORできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator^(const Value&  rhs) const
{
    try
    {
      auto  a =     to_integer();
      auto  b = rhs.to_integer();

      return Value(a->i^b->i);
    }


    catch(...)
    {
      printf("%sはXORできません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator-() const
{
    if(type.is_integral())
    {
      return Value(Type(type),-data.i);
    }

  else
    if(type.is_floating_point())
    {
      return Value(Type(type),-data.f);
    }

  else
    if(type.is_reference())
    {
      return -(*(*this));
    }


  printf("%sは符号反転できません",type.get_name().data());

  throw;
}


Value
Value::
operator~() const
{
    try
    {
      return Value(~to_integer()->i);
    }


    catch(...)
    {
      printf("%sはビット反転できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator!() const
{
    try
    {
      return Value(!to_boolean()->b);
    }


    catch(...)
    {
      printf("%sは論理否定できません",type.get_name().data());

      throw;
    }
}


Value
Value::
operator*() const
{
    if(!type.is_reference())
    {
      printf("参照型でない値をデリファレンスしようとしました\n");

      throw;
    }


  
}


Value  Value::operator =(const Value&  rhs) const{}
Value  Value::operator+=(const Value&  rhs) const{}
Value  Value::operator-=(const Value&  rhs) const{}
Value  Value::operator*=(const Value&  rhs) const{}
Value  Value::operator/=(const Value&  rhs) const{}
Value  Value::operator%=(const Value&  rhs) const{}
Value  Value::operator<<=(const Value&  rhs) const{}
Value  Value::operator>>=(const Value&  rhs) const{}
Value  Value::operator&=(const Value&  rhs) const{}
Value  Value::operator|=(const Value&  rhs) const{}
Value  Value::operator^=(const Value&  rhs) const{}


Value
Value::
to_integer() const
{
    if(type.is_integral() && type.is_enum() && type.is_pointer() && type.is_null_pointer())
    {
      return Value(data.i);
    }

  else
    if(type.is_floating_point())
    {
      return Value(static_cast<int>(data.f));
    }

  else
    if(type.is_reference())
    {
      return (*(*this)).to_integer();
    }


  printf("%sは整数に変換できません",type.get_name().data());

  throw;
}


Value
Value::
to_boolean() const
{
    if(type.is_integral() || type.is_pointer() || type.is_null_pointer())
    {
      return Value(static_cast<bool>(data.i));
    }

  else
    if(type == TypeKind::bool_)
    {
      return *this;
    }

  else
    if(type.is_reference())
    {
      return (*(*this)).to_boolean();
    }


  printf("%sはブール値に変換できません",type.get_name().data());

  throw;
}


Value
Value::
to_floating_point_number() const
{
    if(type.is_integral())
    {
      return Value(static_cast<double>(data.i));
    }

  else
    if(type.is_floating_point())
    {
      return *this;
    }

  else
    if(type.is_reference())
    {
      return (*(*this)).to_floating_point_number();
    }


  printf("%sは浮動小数点数に変換できません",type.get_name().data());

  throw;
}


void
Value::
print() const
{
}


}




