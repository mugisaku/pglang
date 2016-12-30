#ifndef PGLANG_SCOPE_HPP_INCLUDED
#define PGLANG_SCOPE_HPP_INCLUDED


#include<vector>
#include<string>
#include"pglang_expr__value.hpp"
#include"pglang_decl.hpp"




namespace pglang{


struct Decl;


class
Scope
{
protected:
  Scope*  parent;

  std::vector<Scope>  children;

  std::vector<Decl>   decl_table;

public:
  const std::vector<Decl>*  operator->() const;

  void  append(Decl&&  decl);

  Value  get_value(const std::string&  name) const;

  void  print() const;

};


}


#endif




