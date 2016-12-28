#include"pglang_type.hpp"
#include"pglang_expr__literal.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_type__enum.hpp"
#include"pglang_type__union.hpp"
#include"pglang_type__function.hpp"
#include"pglang_decl.hpp"
#include"pglang_scope.hpp"
#include<new>
#include<cstring>




namespace pglang{


Type::Type(): kind(TypeKind::null), name("undefined"){}
Type::Type(Void&&  v): kind(TypeKind::void_), name("void_t"){}
Type::Type(NullPtr&&     nulptr): kind(TypeKind::nullptr_), name("nullptr_t"){}
Type::Type(GenericPtr&&  genptr): kind(TypeKind::genericptr), name("genericptr_t"){}
Type::Type(Bool&&  b): kind(TypeKind::bool_), name("bool"){}
Type::Type(Char8&&   c): kind(TypeKind::char8_), name("char8_t"){}
Type::Type(Char16&&  c): kind(TypeKind::char16_), name("char16_t"){}
Type::Type(Char32&&  c): kind(TypeKind::char32_), name("char32_t"){}
Type::Type(Int8&&   i): kind(TypeKind::int8), name("int8_t"){}
Type::Type(Int16&&  i): kind(TypeKind::int16), name("int16_t"){}
Type::Type(Int32&&  i): kind(TypeKind::int32), name("int32_t"){}
Type::Type(Int64&&  i): kind(TypeKind::int64), name("int64_t"){}
Type::Type(UInt8&&   ui): kind(TypeKind::uint8), name("uint8_t"){}
Type::Type(UInt16&&  ui): kind(TypeKind::uint16), name("uint16_t"){}
Type::Type(UInt32&&  ui): kind(TypeKind::uint32), name("uint32_t"){}
Type::Type(UInt64&&  ui): kind(TypeKind::uint64), name("uint64_t"){}
Type::Type(Float8&&   f): kind(TypeKind::float8), name("float8_t"){}
Type::Type(Float16&&  f): kind(TypeKind::float16), name("float16_t"){}
Type::Type(Float32&&  f): kind(TypeKind::float32), name("float32_t"){}
Type::Type(Float64&&  f): kind(TypeKind::float64), name("float64_t"){}


Type::
Type(Pointer&&  ptr):
kind(TypeKind::pointer),
referred(ptr.type),
name(ptr.type->get_name()+"*")
{
}


Type::
Type(Reference&&  ref):
kind(TypeKind::reference),
referred(ref.type),
name(ref.type->get_name()+"&")
{
}


Type::
Type(const Decl&  decl):
kind(TypeKind::user_defined),
name(decl.get_name())
{
  data.decl = &decl;
}


Type::
Type(const Literal&  lit):
kind(TypeKind::literal),
name("literal")
{
  data.literal = &lit;
}


Type::
Type(const Type&  rhs):
kind(TypeKind::null)
{
  *this = rhs;
}


Type::
Type(Type&&  rhs) noexcept:
kind(TypeKind::null)
{
  *this = std::move(rhs);
}


Type::
~Type()
{
  clear();
}




Type&
Type::
operator=(const Type&  rhs)
{
  clear();

  kind = rhs.kind;
  name = rhs.name;

  referred = rhs.referred;

  data = rhs.data;


  return *this;
}


Type&
Type::
operator=(Type&&  rhs) noexcept
{
  clear();

  name = std::move(rhs.name);

  kind = rhs.kind                 ;
         rhs.kind = TypeKind::null;

  referred = std::move(rhs.referred);

  data = rhs.data;


  return *this;
}


bool
Type::
operator==(const Type&  rhs) const
{
  return(name == rhs.get_name());
}




bool  Type::operator==(TypeKind  k) const{return(kind == k);}
bool  Type::operator!=(TypeKind  k) const{return(kind != k);}


Type::
operator bool() const
{
  return(kind == TypeKind::null);
}


const TypeData*
Type::
operator->() const
{
  return &data;
}


void
Type::
clear()
{
  referred.reset();

  kind = TypeKind::null;
}


const std::string&
Type::get_name() const
{
  return name;
}


TypeKind
Type::
get_kind() const
{
  return kind;
}


Type
Type::
get_referred_type() const
{
    switch(kind)
    {
  case(TypeKind::pointer):
  case(TypeKind::reference):
      return *referred;
      break;
    }


  printf("参照できる型はありません\n");

  throw;
}


size_t
Type::
get_size() const
{
    switch(kind)
    {
  case(TypeKind::nullptr_  ): return    NullPtr::get_size();
  case(TypeKind::genericptr): return GenericPtr::get_size();
  case(TypeKind::bool_): return Bool::get_size();
  case(TypeKind::char8_ ): return Char8::get_size();
  case(TypeKind::char16_): return Char16::get_size();
  case(TypeKind::char32_): return Char32::get_size();
  case(TypeKind::int8 ): return Int8::get_size();
  case(TypeKind::int16): return Int16::get_size();
  case(TypeKind::int32): return Int32::get_size();
  case(TypeKind::int64): return Int64::get_size();
  case(TypeKind::uint8): return UInt8::get_size();
  case(TypeKind::uint16): return UInt16::get_size();
  case(TypeKind::uint32): return UInt32::get_size();
  case(TypeKind::uint64): return UInt64::get_size();
  case(TypeKind::float8): return Float8::get_size();
  case(TypeKind::float16): return Float16::get_size();
  case(TypeKind::float32): return Float32::get_size();
  case(TypeKind::float64): return Float64::get_size();

  case(TypeKind::pointer):
  case(TypeKind::reference):
      return GenericPtr::get_size();
      break;
  case(TypeKind::user_defined):
      break;
  case(TypeKind::literal):
      break;
    }


  return 0;
}


size_t
Type::
get_alignment_size() const
{
    switch(kind)
    {
  case(TypeKind::nullptr_  ): return    NullPtr::get_alignment_size();
  case(TypeKind::genericptr): return GenericPtr::get_alignment_size();
  case(TypeKind::bool_): return Bool::get_alignment_size();
  case(TypeKind::char8_ ): return Char8::get_alignment_size();
  case(TypeKind::char16_): return Char16::get_alignment_size();
  case(TypeKind::char32_): return Char32::get_alignment_size();
  case(TypeKind::int8 ): return Int8::get_alignment_size();
  case(TypeKind::int16): return Int16::get_alignment_size();
  case(TypeKind::int32): return Int32::get_alignment_size();
  case(TypeKind::int64): return Int64::get_alignment_size();
  case(TypeKind::uint8): return UInt8::get_alignment_size();
  case(TypeKind::uint16): return UInt16::get_alignment_size();
  case(TypeKind::uint32): return UInt32::get_alignment_size();
  case(TypeKind::uint64): return UInt64::get_alignment_size();
  case(TypeKind::float8): return Float8::get_alignment_size();
  case(TypeKind::float16): return Float16::get_alignment_size();
  case(TypeKind::float32): return Float32::get_alignment_size();
  case(TypeKind::float64): return Float64::get_alignment_size();

  case(TypeKind::pointer):
  case(TypeKind::reference):
      return GenericPtr::get_alignment_size();
      break;
  case(TypeKind::user_defined):
      break;
  case(TypeKind::literal):
      break;
    }


  return 0;
}




}




