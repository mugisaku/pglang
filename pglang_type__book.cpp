#include"pglang_type__book.hpp"




namespace pglang{




void
Book::
append(StructDeclaration&&  decl)
{
  stdecl_table.emplace_back(std::move(decl));

  stdecl_table.back().book = this;
}


void
Book::
append(EnumDeclaration&&  decl)
{
  endecl_table.emplace_back(std::move(decl));

  endecl_table.back().book = this;
}


void
Book::
append(UnionDeclaration&&  decl)
{
  undecl_table.emplace_back(std::move(decl));

  undecl_table.back().book = this;
}


void
Book::
append(FunctionDeclaration&&  decl)
{
  fndecl_table.emplace_back(std::move(decl));

  fndecl_table.back().book = this;
}




StructDeclaration*
Book::
find_struct(const char*  name)
{
  return const_cast<StructDeclaration*>(find_struct(name));
}


EnumDeclaration*
Book::
find_enum(const char*  name)
{
  return const_cast<EnumDeclaration*>(find_enum(name));
}


UnionDeclaration*
Book::find_union(const char*  name)
{
  return const_cast<UnionDeclaration*>(find_union(name));
}


FunctionDeclaration*
Book::
find_function(const char*  name)
{
  return const_cast<FunctionDeclaration*>(find_function(name));
}


const StructDeclaration*
Book::
find_struct(const char*  name) const
{
    for(auto&  decl: stdecl_table)
    {
        if(decl.name == name)
        {
          return &decl;
        }
    }


  return nullptr;
}


const EnumDeclaration*
Book::
find_enum(const char*  name) const
{
    for(auto&  decl: endecl_table)
    {
        if(decl.name == name)
        {
          return &decl;
        }
    }


  return nullptr;
}


const UnionDeclaration*
Book::
find_union(const char*  name) const
{
    for(auto&  decl: undecl_table)
    {
        if(decl.name == name)
        {
          return &decl;
        }
    }


  return nullptr;
}


const FunctionDeclaration*
Book::
find_function(const char*  name) const
{
    for(auto&  decl: fndecl_table)
    {
        if(decl.name == name)
        {
          return &decl;
        }
    }


  return nullptr;
}




void
Book::
print() const
{
    for(auto&  decl: stdecl_table)
    {
      decl.print();

      printf("\n");
    }


    for(auto&  decl: endecl_table)
    {
      decl.print();

      printf("\n");
    }


    for(auto&  decl: undecl_table)
    {
      decl.print();

      printf("\n");
    }


    for(auto&  decl: fndecl_table)
    {
      decl.print();

      printf("\n");
    }
}


}




