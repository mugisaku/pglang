#ifndef PGLANG_STMT_HPP_INCLUDED
#define PGLANG_STMT_HPP_INCLUDED


#include<vector>




namespace pglang{


enum class
StmtKind
{
  null,

  declaration,
  expression,
  return_,

};


struct
StmtData
{
  Expr*  expr;

};


class
Stmt
{
  StmtKind  kind;
  StmtData  data;

public:

};


}


#endif




