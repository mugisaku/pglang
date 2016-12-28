#ifndef PGLANG_DECL_HPP_INCLUDED
#define PGLANG_DECL_HPP_INCLUDED


#include"pglang_type__struct.hpp"
#include"pglang_type__enum.hpp"
#include"pglang_type__union.hpp"
#include"pglang_type__array.hpp"
#include"pglang_type__function.hpp"




namespace pglang{


enum class
DeclKind
{
  null,

  variable,
  constant,
  function,
  array,
  struct_,
  enum_,
  union_,
};


union
DeclData
{
  Parameter  pa;
  Array      ar;
  Struct     st;
  Enum       en;
  Union      un;
  Function   fn;

   DeclData(){}
  ~DeclData(){}

};


class
Decl
{
  DeclKind  kind;
  DeclData  data;

  std::string  name;

public:
   Decl();
   Decl(std::string&&  name_, Struct&&    st);
   Decl(std::string&&  name_, Enum&&      en);
   Decl(std::string&&  name_, Union&&     un);
   Decl(std::string&&  name_, Array&&     ar);
   Decl(std::string&&  name_, Function&&  fn);
   Decl(      Decl&&  rhs) noexcept;
   Decl(const Decl&   rhs)         ;
  ~Decl();

  const DeclData*  operator->() const;

  Decl&  operator=(      Decl&&  rhs);
  Decl&  operator=(const Decl&   rhs);

  void  clear();

  const std::string&  get_name() const;

  DeclKind  get_kind() const;

  void  print() const;

};


}


#endif




