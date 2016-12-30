#ifndef PGLANG_STMT_HPP_INCLUDED
#define PGLANG_STMT_HPP_INCLUDED


#include"pglang_expr.hpp"
#include"pglang_decl.hpp"




namespace pglang{


enum class
StmtKind
{
  null,

  declaration,
  expression,
  block,
  return_,

};


struct
Return
{
  Expr*  expr;

  Return(Expr*  expr_=nullptr): expr(expr_){}

};


struct Scope;
struct Block;


struct
StmtData
{
  const Decl*  decl;

  Block*  block;
  Expr*    expr;

};


class
Stmt
{
  StmtKind  kind;
  StmtData  data;

public:
   Stmt(const Decl&  decl);
   Stmt(Expr*  expr);
   Stmt(Block*  block);
   Stmt(Return&&  ret);
   Stmt(      Stmt&&  rhs) noexcept;
   Stmt(const Stmt&   rhs)         ;
  ~Stmt();


  Stmt&  operator=(      Stmt&&  rhs) noexcept;
  Stmt&  operator=(const Stmt&   rhs)         ;

  void  clear();

   void  execute(const Scope*  scope) const;

  void  print() const;

};


}


#endif




