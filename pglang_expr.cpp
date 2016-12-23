#include"pglang_expr.hpp"




namespace pglang{


Expr::Expr(){}
Expr::Expr(     Element&&  el) noexcept: element(std::move(el)){}
Expr::Expr(const Element&  el)         : element(el){}


Value
Expr::
calculate() const
{
    switch(element.get_kind())
    {
      case(ElementKind::null):
        return left->calculate();
        break;
      case(ElementKind::operand):
        {
          auto&  op = element->operand;

            switch(op.get_kind())
            {
              case(LiteralKind::identifier):
//                return Value(&root_object[op.data.identifier]);
                break;
              case(LiteralKind::expression):
                return op->expr->calculate();
                break;
              case(LiteralKind::integer):
                return Value(op->i);
                break;
            }
        }
        break;
      case(ElementKind::unary_operator):
        {
          auto  v = left->calculate();

          auto  l = *v;

            switch(element->operator_)
            {
              case(Operator('!')): v = Value(!l);break;
              case(Operator('~')): v = Value(~l);break;
              case(Operator('-')): v = Value(-l);break;
            }


          return v;
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  op = element->operator_;

          auto  lv = left->calculate();
          auto  l = *lv;

          auto  ro = right->element->operand;

            switch(op)
            {
              case(Operator('.')):
                {
/*
                    if(!lv.object)
                    {
                      printf("左辺がオブジェクトではありません\n");

                      throw;
                    }


                    if(ro.kind != OperandKind::identifier)
                    {
                      printf("右辺が識別子ではありません\n");

                      throw;
                    }


                  return Value(&(*lv.object)[ro.data.identifier]);
*/
                }
                break;
            }


          auto  rv = right->calculate();
          auto  r = *rv;

            switch(op)
            {
              case(Operator('*')): lv = Value(l*r);break;
              case(Operator('/')): lv = Value(l/r);break;
              case(Operator('%')): lv = Value(l%r);break;

              case(Operator('+')): lv = Value(l+r);break;
              case(Operator('-')): lv = Value(l-r);break;

              case(Operator('<','<')): lv = Value(l<<r);break;
              case(Operator('>','>')): lv = Value(l>>r);break;

              case(Operator('<')    ): lv = Value(l< r);break;
              case(Operator('<','=')): lv = Value(l<=r);break;
              case(Operator('>')    ): lv = Value(l> r);break;
              case(Operator('>','=')): lv = Value(l>=r);break;

              case(Operator('=','=')): lv = Value(l==r);break;
              case(Operator('!','=')): lv = Value(l!=r);break;


              case(Operator('&')): lv = Value(l&r);break;
              case(Operator('|')): lv = Value(l|r);break;
              case(Operator('^')): lv = Value(l^r);break;

              case(Operator('&','&')): lv = Value(l&&r);break;
              case(Operator('|','|')): lv = Value(l&&r);break;

              case(Operator('<','<','=')): l <<= r;break;
              case(Operator('>','>','=')): l >>= r;break;
              case(Operator('+','=')): l += r;break;
              case(Operator('-','=')): l -= r;break;
              case(Operator('*','=')): l *= r;break;
              case(Operator('/','=')): l /= r;break;
              case(Operator('%','=')): l %= r;break;
              case(Operator('&','=')): l &= r;break;
              case(Operator('|','=')): l |= r;break;
              case(Operator('^','=')): l ^= r;break;
              case(Operator('=')    ): l  = r;break;
            }


          return lv;
        }
        break;
    }


  return Value(0);
}


void
Expr::
print() const
{
    switch(element.get_kind())
    {
      case(ElementKind::null):
        left->print();
        break;
      case(ElementKind::operand):
        element.print();
        break;
      case(ElementKind::unary_operator):
        printf("(");

        element.print();

        left->print();

        printf(")");
        break;
      case(ElementKind::binary_operator):
        printf("(");
 
        left->print();

        element.print();

        right->print();

        printf(")");
        break;
    }
}


namespace{
void
merge(std::list<Expr*>&  buf, std::vector<Element>&  uols)
{
  auto  it = uols.rbegin();
  auto end = uols.rend();

    while(it != end)
    {
      buf.emplace_back(new Expr(std::move(*it++)));
    }
}
}


std::list<Expr*>
Expr::
to_rpn(std::vector<Element>&&  src)
{
  std::list<Expr*>  dst;

  std::vector<Element>   unary_operator_stack;
  std::vector<Element>  binary_operator_stack;

    for(auto&  el: src)
    {
        switch(el.get_kind())
        {
          case(ElementKind::unary_operator):
            unary_operator_stack.emplace_back(el);
            break;
          case(ElementKind::binary_operator):
            {
              auto  cur_preced = el.get_precedence().number;

                if(unary_operator_stack.size())
                {
                  auto  tail_preced = unary_operator_stack.back().get_precedence().number;

                    if(cur_preced >= tail_preced)
                    {
                        for(auto&  unop: unary_operator_stack)
                        {
                          binary_operator_stack.emplace_back(std::move(unop));
                        }
                    }

                  else
                    {
                      merge(dst,unary_operator_stack);
                    }


                  unary_operator_stack.clear();
                }


                while(binary_operator_stack.size())
                {
                  auto&  tail = binary_operator_stack.back();

                  auto  tail_preced = tail.get_precedence().number;

                    if(cur_preced <= tail_preced)
                    {
                        if((cur_preced == tail_preced) &&
                           (tail.get_associativity() == Associativity::right_to_left))
                        {
                          break;
                        }

                      else
                        {
                          dst.emplace_back(new Expr(std::move(tail)));

                          binary_operator_stack.pop_back();
                        }
                    }

                  else
                    {
                      break;
                    }
                }


  	           binary_operator_stack.emplace_back(el);
            }
            break;
          case(ElementKind::operand):
            dst.emplace_back(new Expr(std::move(el)));
            break;
        }
    }


  merge(dst, unary_operator_stack);
  merge(dst,binary_operator_stack);

  return std::move(dst);
}


Expr*
Expr::
create_tree(std::list<Expr*>&&  ls)
{
  std::vector<Expr*>  operand_buf;

    while(ls.size())
    {
      auto  nd = ls.front();
                 ls.pop_front();

        switch(nd->element.get_kind())
        {
          case(ElementKind::operand):
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::unary_operator):
              if(operand_buf.size() < 1)
              {
                printf("単項演算オペランドの数が足りません\n");
                throw;
              }


            nd->left = operand_buf.back();

            operand_buf.pop_back();
            operand_buf.emplace_back(nd);
            break;
          case(ElementKind::binary_operator):
              if(operand_buf.size() < 2)
              {
                printf("二項演算オペランドの数が足りません\n");
                throw;
              }


            nd->right = operand_buf.back();

            operand_buf.pop_back();

            nd->left = operand_buf.back();

            operand_buf.pop_back();


            operand_buf.emplace_back(nd);
            break;
        }
    }


    if(operand_buf.size() != 1)
    {
      printf("結果が不正でした\n");
      throw;
    }


  return operand_buf.front();
}


}




