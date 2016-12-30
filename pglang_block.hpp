#ifndef PGLANG_BLOCK_HPP_INCLUDED
#define PGLANG_BLOCK_HPP_INCLUDED


#include"pglang_scope.hpp"
#include"pglang_stmt.hpp"




namespace pglang{


class
Block: public Scope
{
  std::vector<Stmt>  stmt_list;

public:
  virtual ~Block(){}


  const std::vector<Stmt>*  operator->() const;

  void  append(Stmt&&  stmt);

  virtual void  print() const;

};


}


#endif




