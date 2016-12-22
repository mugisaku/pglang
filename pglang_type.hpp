#ifndef PGLANG_TYPE_HPP_INCLUDED
#define PGLANG_TYPE_HPP_INCLUDED


#include<cstddef>
#include<cstdio>
#include<string>
#include"pglang_type__primitive.hpp"
#include"aunique_ptr"




namespace pglang{


struct Function;
struct Book;
struct ArgumentList;


struct Void{};


enum class
TypeKind
{
  null,

  void_,

  nullptr_,
  genericptr,

  bool_,
  char8_,
  char16_,
  char32_,
  int8,
  int16,
  int32,
  int64,
  uint8,
  uint16,
  uint32,
  uint64,
  float8,
  float16,
  float32,
  float64,

  reference,
  pointer,
  array,

  enum_,
  union_,
  struct_,

  function,

  argument_list,

};


struct Pointer;
struct Reference;
struct Array;
struct StructDeclaration;
struct EnumDeclaration;
struct UnionDeclaration;
struct FunctionDeclaration;


class
Type
{
  TypeKind  kind;

  Book*  book;

  std::string  name;

  aunique_ptr<Type>  referred;

  size_t  array_size;

  union Data{
    char*    str;
    const ArgumentList*  args;

     Data(){};
    ~Data(){};

  } data;

public:
  Type(Book*  book_=nullptr);
  Type(Void&&  v);
  Type(NullPtr&&     nulptr);
  Type(GenericPtr&&  genptr);
  Type(Bool&&  b);
  Type(Char8&&   c);
  Type(Char16&&  c);
  Type(Char32&&  c);
  Type(Int8&&   i);
  Type(Int16&&  i);
  Type(Int32&&  i);
  Type(Int64&&  i);
  Type(UInt8&&   ui);
  Type(UInt16&&  ui);
  Type(UInt32&&  ui);
  Type(UInt64&&  ui);
  Type(Float8&&   f);
  Type(Float16&&  f);
  Type(Float32&&  f);
  Type(Float64&&  f);
  Type(Array&&  arr);
  Type(Pointer&&  ptr);
  Type(Reference&&  ref);
  Type(const StructDeclaration&  decl);
  Type(const EnumDeclaration&  decl);
  Type(const UnionDeclaration&  decl);
  Type(const FunctionDeclaration&  decl);
  Type(const ArgumentList*  args);
  Type(const Type&   rhs)         ;
  Type(      Type&&  rhs) noexcept;
 ~Type(                    );


  Type&  operator=(const Type&   rhs)         ;
  Type&  operator=(      Type&&  rhs) noexcept;

  bool  operator==(TypeKind  k) const;
  bool  operator!=(TypeKind  k) const;

  bool  operator==(const Type&  rhs) const;

  operator bool() const;

  void  clear();

  Book*  get_book() const;

  const std::string&  get_name() const;

  TypeKind  get_kind() const;

  size_t  get_size() const;
  size_t  get_alignment_size() const;

  bool  is_void() const;
  bool  is_valid() const;
  bool  is_function() const;
  bool  is_nullptr() const;
  bool  is_pointer() const;
  bool  is_array() const;
  bool  is_reference() const;
  bool  is_integer() const;
  bool  is_boolean() const;
  bool  is_enum() const;
  bool  is_union() const;
  bool  is_struct() const;

  bool  is_object() const;
  bool  is_scalar() const;
  bool  is_arithmetic() const;
  bool  is_fundamental() const;
  bool  is_compound() const;
  bool  is_literal() const;
  bool  is_signed() const;
  bool  is_unsigned() const;

};




struct
Pointer
{
  Type*  type;

  Pointer(Type&&  t): type(new Type(std::move(t))){}

};


struct
Reference
{
  Type*  type;

  Reference(Type&&  t): type(new Type(std::move(t))){}

};


struct
Array
{
  Type*  type;

  size_t  size;

  Array(Type&&  t, size_t  size_):
  type(new Type(std::move(t))),
  size(size_) {}

};




}


#endif




