#ifndef PGLANG_SCOPE_HPP_INCLUDED
#define PGLANG_SCOPE_HPP_INCLUDED


#include<vector>




namespace pglang{


struct Decl;


class
Scope
{
  Scope*  parent;

  std::vector<Scope*>  children;

  std::vector<Decl*>   decl_table;

public:
  const std::vector<Decl*>*  operator->() const;

  void  append(Decl*  decl);

  void  print() const;

};


}


#endif




