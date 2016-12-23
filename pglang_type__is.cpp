#include"pglang_type.hpp"





namespace pglang{


bool  Type::is_void()      const{return(kind == TypeKind::void_);}
bool  Type::is_function()  const{return(kind == TypeKind::function);}
bool  Type::is_null_pointer()const{return(kind == TypeKind::nullptr_);}
bool  Type::is_pointer()   const{return(kind == TypeKind::pointer);}
bool  Type::is_array()     const{return(kind == TypeKind::array);}
bool  Type::is_reference() const{return(kind == TypeKind::reference);}
bool  Type::is_lvalue_reference() const{return(kind == TypeKind::reference);}
bool  Type::is_rvalue_reference() const{return(kind == TypeKind::reference);}
bool  Type::is_enum()      const{return(kind == TypeKind::enum_);}
bool  Type::is_struct()    const{return(kind == TypeKind::struct_);}
bool  Type::is_union()     const{return(kind == TypeKind::union_);}


bool
Type::
is_integral() const
{
  return((kind == TypeKind::char8_ ) ||
         (kind == TypeKind::char16_) ||
         (kind == TypeKind::char32_) ||
         (kind == TypeKind::bool_  ) ||
         (kind == TypeKind::int8   ) ||
         (kind == TypeKind::uint8  ) ||
         (kind == TypeKind::int16  ) ||
         (kind == TypeKind::uint16 ) ||
         (kind == TypeKind::int32  ) ||
         (kind == TypeKind::uint32 ) ||
         (kind == TypeKind::int64  ) ||
         (kind == TypeKind::uint64 ));
}


bool
Type::
is_floating_point() const
{
  return((kind == TypeKind::float8 ) ||
         (kind == TypeKind::float16) ||
         (kind == TypeKind::float32) ||
         (kind == TypeKind::float64));
}


bool  Type::is_arithmetic() const{return is_integral()||is_floating_point();}
bool  Type::is_fundamental() const{return is_arithmetic()||is_null_pointer()||is_void();}
bool  Type::is_object() const{return(is_enum()||is_struct()||is_union()||is_array()||is_scalar());}
bool  Type::is_scalar() const{return(is_arithmetic()||is_enum()||is_pointer()||is_null_pointer());}
bool  Type::is_compound() const{return(is_array()||is_function()||is_pointer()||is_reference()||is_struct()||is_union()||is_enum());}


bool
Type::
is_literal() const
{
  return(is_scalar()||
           is_void()||
         (is_reference() && referred->is_literal())||
         (is_array()     && referred->is_literal()));
}


bool
Type::
is_signed() const
{
  return((kind == TypeKind::int8  ) ||
         (kind == TypeKind::int16 ) ||
         (kind == TypeKind::int32 ) ||
         (kind == TypeKind::int64 ));
}


bool
Type::
is_unsigned() const
{
  return((kind == TypeKind::char8_ ) ||
         (kind == TypeKind::char16_) ||
         (kind == TypeKind::char32_) ||
         (kind == TypeKind::bool_  ) ||
         (kind == TypeKind::uint8  ) ||
         (kind == TypeKind::uint16 ) ||
         (kind == TypeKind::uint32 ) ||
         (kind == TypeKind::uint64 ));
}




}




