#include"pglang_expr__value.hpp"
#include"pglang_expr__literal.hpp"
#include"pglang_type.hpp"
#include<cinttypes>
#include<new>




namespace pglang{




Value::Value(){}
Value::Value(Type&&  type_): type(std::move(type_)){}
Value::Value(Type&&  type_, int64_t  i): type(std::move(type_)){data.i = i;}
Value::Value(Type&&  type_, uint64_t  u): type(std::move(type_)){data.u = u;}
Value::Value(Type&&  type_, double  f): type(std::move(type_)){data.f = f;}
Value::Value(const Literal&  l): type(l.get_type()){data.l = &l;}
Value::Value(nullptr_t  nulptr): type(NullPtr()){;}
Value::Value(bool  b): type(Bool()){data.b = b;}
Value::Value(int64_t  i): type(Int()){data.i = i;}
Value::Value(uint64_t  u): type(UInt()){data.u = u;}
Value::Value(double    f): type(Float()){data.f = f;}
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
operator[](const Value&  rhs) const
{
}


Value
Value::
operator()(const Value&  rhs) const
{
}


Value
Value::
to_integer() const
{
    if(type == TypeKind::literal)
    {
      return Value(Type(Int()),(*data.l)->i);
    }

  else
    if(type.is_integral() || type.is_enum() || type.is_pointer() || type.is_null_pointer())
    {
      return Value(Type(Int()),data.i);
    }

  else
    if(type.is_floating_point())
    {
      return Value(Type(Float()),static_cast<int64_t>(data.f));
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
      return Value(Type(Bool()),data.i);
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
      return Value(Type(Float()),static_cast<double>(data.i));
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
  printf("%s(",type.get_name().data());

    if(type == TypeKind::literal)
    {
      printf("%" PRId64,(*data.l)->i);
    }

  else
    if(type.is_integral() || type.is_enum() || type.is_pointer() || type.is_null_pointer())
    {
      printf("%" PRId64,data.i);
    }

  else
    if(type.is_floating_point())
    {
      printf("%f",data.f);
    }

  else
    if(type.is_reference())
    {
    }


  printf(")");
}


}




