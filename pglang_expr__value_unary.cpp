#include"pglang_expr__value.hpp"
#include"pglang_type.hpp"
#include<new>




namespace pglang{




Value
Value::
operator-() const
{
    if(type.is_integral())
    {
      return Value(Type(Int()),-data.i);
    }

  else
    if(type.is_floating_point())
    {
      return Value(Type(Int()),-data.f);
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
      return Value(Type(Int()),~to_integer()->i);
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
      return Value(Type(Bool()),static_cast<int64_t>(!to_boolean()->i));
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
    if(!type.is_pointer())
    {
      printf("ポインタ型でない値を参照しようとしました\n");

      throw;
    }


  return Value(Reference(Type(type.get_referred_type())),data.i);
}


Value
Value::
operator&() const
{
    if(!type.is_reference())
    {
      printf("参照型以外のアドレスは取得できません\n");

      throw;
    }


  return Value(Pointer(Type(type.get_referred_type())),data.i);
}




}




