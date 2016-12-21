#include"pglang_type.hpp"





namespace pglang{


bool  Type::is_void()      const{return(is_fundamental() && (data.fdm.kind == FundamentalKind::void_));}
bool  Type::is_valid()      const{return !is_void();}
bool  Type::is_function()  const{return(kind == TypeKind::function);}
bool  Type::is_nullptr()   const{return(is_fundamental() && (data.fdm.kind == FundamentalKind::nullptr_));}
bool  Type::is_boolean()   const{return(is_fundamental() && (data.fdm.kind == FundamentalKind::bool_));}
bool  Type::is_pointer()   const{return(kind == TypeKind::pointer);}
bool  Type::is_array()     const{return(kind == TypeKind::array);}
bool  Type::is_reference() const{return(kind == TypeKind::reference);}
bool  Type::is_enum()      const{return(kind == TypeKind::enum_);}
bool  Type::is_struct()    const{return(kind == TypeKind::struct_);}
bool  Type::is_union()     const{return(kind == TypeKind::union_);}


bool
Type::
is_integer() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::char_ ) ||
          (data.fdm.kind == FundamentalKind::bool_ ) ||
          (data.fdm.kind == FundamentalKind::int8  ) ||
          (data.fdm.kind == FundamentalKind::uint8 ) ||
          (data.fdm.kind == FundamentalKind::int16 ) ||
          (data.fdm.kind == FundamentalKind::uint16) ||
          (data.fdm.kind == FundamentalKind::int32 )));
}


bool  Type::is_arithmetic() const{return is_integer();}
bool  Type::is_fundamental() const{return (kind == TypeKind::fundamental);}
bool  Type::is_object() const{return(is_enum()||is_struct()||is_union()||is_array()||is_scalar());}
bool  Type::is_scalar() const{return(is_arithmetic()||is_enum()||is_pointer()||is_nullptr());}
bool  Type::is_compound() const{return(is_array()||is_function()||is_pointer()||is_reference()||is_struct()||is_union()||is_enum());}


bool
Type::
is_literal() const
{
  return(is_scalar()||
           is_void()||
         (is_reference() && data.ptr.referred->is_literal())|
         (is_array()     && data.arr.type->is_literal()));
}


bool
Type::
is_signed() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::int8  ) ||
          (data.fdm.kind == FundamentalKind::int16 ) ||
          (data.fdm.kind == FundamentalKind::int32 )));
}


bool
Type::
is_unsigned() const
{
  return(is_fundamental() &&
         ((data.fdm.kind == FundamentalKind::char_ ) ||
          (data.fdm.kind == FundamentalKind::bool_ ) ||
          (data.fdm.kind == FundamentalKind::uint8 ) ||
          (data.fdm.kind == FundamentalKind::uint16)));
}




}




