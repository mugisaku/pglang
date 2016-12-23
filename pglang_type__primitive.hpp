#ifndef PGLANG_TYPE__PRIMITIVE_HPP_INCLUDED
#define PGLANG_TYPE__PRIMITIVE_HPP_INCLUDED


#include<cstdint>
#include<cstddef>




namespace pglang{


template<int  BYTE_NUMBER, bool  SIGN>
struct
Primitive
{
  static constexpr bool  sign(){return SIGN;}

  static constexpr size_t  get_size()          {return BYTE_NUMBER;}
  static constexpr size_t  get_alignment_size(){return BYTE_NUMBER;}

};


using UInt8  = Primitive<1,false>;
using UInt16 = Primitive<2,false>;
using UInt32 = Primitive<4,false>;
using UInt64 = Primitive<8,false>;

using Int8  = Primitive<1,true>;
using Int16 = Primitive<2,true>;
using Int32 = Primitive<4,true>;
using Int64 = Primitive<8,true>;

struct Float8 : Primitive<1,true>{};
struct Float16: Primitive<2,true>{};
struct Float32: Primitive<4,true>{};
struct Float64: Primitive<8,true>{};

struct Char8 : Primitive<1,false>{};
struct Char16: Primitive<2,false>{};
struct Char32: Primitive<4,false>{};

struct Bool: Primitive<1,false>{};

struct    NullPtr: Primitive<4,false>{};
struct GenericPtr: Primitive<4,false>{};

using Char  = Char8;
using Int   = Int32;
using Uint  = UInt32;
using Float = Float32;


}


#endif




