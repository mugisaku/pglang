#ifndef PGLANG_TYPE__BOOK_HPP_INCLUDED
#define PGLANG_TYPE__BOOK_HPP_INCLUDED


#include"pglang_type__struct.hpp"
#include"pglang_type__enum.hpp"
#include"pglang_type__union.hpp"
#include"pglang_type__function.hpp"




namespace pglang{


class
Book
{
  std::vector<StructDeclaration>    stdecl_table;
  std::vector<EnumDeclaration>      endecl_table;
  std::vector<UnionDeclaration>     undecl_table;
  std::vector<FunctionDeclaration>  fndecl_table;

public:
  void  append(StructDeclaration&&  decl);
  void  append(EnumDeclaration&&  decl);
  void  append(UnionDeclaration&&  decl);
  void  append(FunctionDeclaration&&  decl);

        StructDeclaration*  find_struct(const char*  name);
  const StructDeclaration*  find_struct(const char*  name) const;
        EnumDeclaration*  find_enum(const char*  name);
  const EnumDeclaration*  find_enum(const char*  name) const;
        UnionDeclaration*  find_union(const char*  name);
  const UnionDeclaration*  find_union(const char*  name) const;
        FunctionDeclaration*  find_function(const char*  name);
  const FunctionDeclaration*  find_function(const char*  name) const;

  void  print() const;

};


}


#endif




