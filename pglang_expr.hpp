#ifndef PGLANG_EXPR_HPP_INCLUDED
#define PGLANG_EXPR_HPP_INCLUDED


#include<vector>
#include<list>
#include<cstdio>
#include"pglang_expr__element.hpp"
#include"pglang_expr__value.hpp"
#include"aunique_ptr"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{


class
Expr
{
  Element  element;

  aunique_ptr<Expr>   left;
  aunique_ptr<Expr>  right;

public:
  Expr();
  Expr(Element&&  el);


  Value  to_value() const;

  void  print() const;

  static std::list<Expr*>  to_rpn(std::vector<Element>&&  src);

  static Expr*  create_tree(std::list<Expr*>&&  ls);

};


}


#endif




