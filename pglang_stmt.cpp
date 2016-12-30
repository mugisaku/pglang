#include"pglang_stmt.hpp"
#include"pglang_block.hpp"




namespace pglang{




Stmt::Stmt(const Decl&  decl): kind(StmtKind::declaration){data.decl = &decl;}
Stmt::Stmt(Expr*  expr): kind(StmtKind::expression){data.expr = expr;}
Stmt::Stmt(Block*  block): kind(StmtKind::block){data.block = block;}
Stmt::Stmt(Return&&  ret): kind(StmtKind::return_){data.expr = ret.expr;}


Stmt::Stmt(      Stmt&&  rhs) noexcept: kind(StmtKind::null){*this = std::move(rhs);}
Stmt::Stmt(const Stmt&   rhs)         : kind(StmtKind::null){*this = rhs;}


Stmt::
~Stmt()
{
  clear();
}




Stmt&
Stmt::
operator=(Stmt&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(StmtKind::expression):
  case(StmtKind::return_):
      data.expr = rhs.data.expr;
      break;
  case(StmtKind::declaration):
      data.decl = rhs.data.decl;
      break;
  case(StmtKind::block):
      data.block = rhs.data.block;
      break;
    }


  return *this;
}


Stmt&
Stmt::
operator=(const Stmt&   rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(StmtKind::expression):
  case(StmtKind::return_):
      data.expr = rhs.data.expr? new Expr(*rhs.data.expr):nullptr;
      break;
  case(StmtKind::block):
      data.block = new Block(*rhs.data.block);
      break;
    }


  return *this;
}


void
Stmt::
clear()
{
    switch(kind)
    {
  case(StmtKind::expression):
  case(StmtKind::return_):
      delete data.expr;
      break;
  case(StmtKind::declaration):
      break;
  case(StmtKind::block):
      delete data.block;
      break;
    }


  kind = StmtKind::null;
}


void
Stmt::
execute(const Scope*  scope) const
{
    switch(kind)
    {
  case(StmtKind::expression):
      break;
  case(StmtKind::return_):
      break;
  case(StmtKind::declaration):
      break;
  case(StmtKind::block):
      break;
    }
}


void
Stmt::
print() const
{
    switch(kind)
    {
  case(StmtKind::expression):
      data.expr->print();
      break;
  case(StmtKind::return_):
      printf("return ");
        if(data.expr)
        {
          data.expr->print();
        }
      break;
  case(StmtKind::declaration):
      data.decl->print();
      break;
  case(StmtKind::block):
      data.block->print();
      break;
    }
}



}




