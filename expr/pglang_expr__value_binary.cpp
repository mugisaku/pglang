#include"pglang_expr__value.hpp"
#include"pglang_type.hpp"
#include<new>




namespace pglang{




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


}




