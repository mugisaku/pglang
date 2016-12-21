#include"pglang_type.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_type__enum.hpp"
#include"pglang_type__union.hpp"
#include"pglang_type__function.hpp"
#include"pglang_type__book.hpp"
#include<new>
#include<cstring>




namespace pglang{


Type::Type(Book*  book_): kind(TypeKind::null), book(book_), name("undefined"){}
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
Type(Type&&  type, size_t  array_size_):
book(type.get_book()),
kind(TypeKind::array),
array_size(array_size_),
name(type.get_name()+"["+std::to_string(array_size_)+"]"),
referred(new Type(std::move(type)))
{
}


Type::
Type(Pointer&&  ptr):
book(ptr.type->get_book()),
kind(TypeKind::pointer),
referred(ptr.type),
name(ptr.type->get_name()+"*")
{
}


Type::
Type(Reference&&  ref):
book(ref.type->get_book()),
kind(TypeKind::reference),
referred(ref.type),
name(ref.type->get_name()+"&")
{
}


Type::
Type(const StructDeclaration&  decl):
book(decl.book),
kind(TypeKind::struct_),
name(decl.name)
{
}


Type::
Type(const EnumDeclaration&  decl):
book(decl.book),
kind(TypeKind::enum_),
name(decl.name)
{
}


Type::
Type(const UnionDeclaration&  decl):
book(decl.book),
kind(TypeKind::union_),
name(decl.name)
{
}


Type::
Type(const FunctionDeclaration&  decl):
book(decl.book),
kind(TypeKind::function),
name(decl.name)
{
}


Type::
Type(const ArgumentList*  args):
kind(TypeKind::argument_list)
{
  data.args = args;
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
  book = rhs.book;
  name = rhs.name;

  array_size = rhs.array_size;

  referred = rhs.referred;

    switch(kind)
    {
  case(TypeKind::array):
      break;
  case(TypeKind::pointer):
  case(TypeKind::reference):
      break;
  case(TypeKind::struct_):
  case(TypeKind::union_):
  case(TypeKind::enum_):
  case(TypeKind::function):
      data.str = new char[std::strlen(rhs.data.str)+1];
      std::strcpy(data.str,rhs.data.str);
      break;
  case(TypeKind::argument_list):
      data.args = rhs.data.args;
      break;
    }


  return *this;
}


Type&
Type::
operator=(Type&&  rhs) noexcept
{
  clear();

  name = std::move(rhs.name);

  book = rhs.book;
  kind = rhs.kind                 ;
         rhs.kind = TypeKind::null;

  array_size = rhs.array_size;

  referred = std::move(rhs.referred);

    switch(kind)
    {
  case(TypeKind::array):
      break;
  case(TypeKind::pointer):
  case(TypeKind::reference):
      break;
  case(TypeKind::struct_):
  case(TypeKind::union_):
  case(TypeKind::enum_):
  case(TypeKind::function):
      data.str = rhs.data.str;
      break;
  case(TypeKind::argument_list):
      data.args = rhs.data.args;
      break;
    }


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




void
Type::
clear()
{
    switch(kind)
    {
  case(TypeKind::array):
  case(TypeKind::pointer):
  case(TypeKind::reference):
      referred.reset();
      break;
  case(TypeKind::struct_):
  case(TypeKind::union_):
  case(TypeKind::enum_):
  case(TypeKind::function):
      delete[] data.str;
      break;
  default:;
    }


  kind = TypeKind::null;
}


const std::string&
Type::get_name() const
{
  return name;
}


Book*
Type::
get_book() const
{
  return book;
}


TypeKind
Type::
get_kind() const
{
  return kind;
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

  case(TypeKind::array):
      return referred->get_size()*array_size;
      break;
  case(TypeKind::pointer):
  case(TypeKind::reference):
      return GenericPtr::get_size();
      break;
  case(TypeKind::enum_):
      return Enum::get_size();
      break;
  case(TypeKind::struct_):
        if(!book)
        {
          throw;
        }

      else
        {
          auto  decl = book->find_struct(data.str);

            if(!decl || decl->definition)
            {
              throw;
            }


          return decl->definition->get_size();
        }
      break;
  case(TypeKind::union_):
        if(!book)
        {
          throw;
        }

      else
        {
          auto  decl = book->find_union(data.str);

            if(!decl || decl->definition)
            {
              throw;
            }


          return decl->definition->get_size();
        }
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

  case(TypeKind::array):
      return referred->get_alignment_size();
      break;
  case(TypeKind::pointer):
  case(TypeKind::reference):
      return GenericPtr::get_alignment_size();
      break;
  case(TypeKind::enum_):
      return Enum::get_alignment_size();
      break;
  case(TypeKind::struct_):
        if(!book)
        {
          throw;
        }

      else
        {
          auto  decl = book->find_struct(data.str);

            if(!decl || decl->definition)
            {
              throw;
            }


          return decl->definition->get_alignment_size();
        }
      break;
  case(TypeKind::union_):
        if(!book)
        {
          throw;
        }

      else
        {
          auto  decl = book->find_union(data.str);

            if(!decl || decl->definition)
            {
              throw;
            }


          return decl->definition->get_alignment_size();
        }
      break;
    }


  return 0;
}




}




