#include"pglang_expr.hpp"




namespace pglang{


Expr::Expr(){}
Expr::Expr(Element&&  el): element(std::move(el)){}


Value
Expr::
to_value() const
{
    switch(element.get_kind())
    {
      case(ElementKind::null):
        return left->to_value();
        break;
      case(ElementKind::identifier):
printf("未実装");
throw;
        break;
      case(ElementKind::literal):
        return element->literal.to_value();
        break;
      case(ElementKind::argument_list):
printf("未実装");
throw;
        break;
      case(ElementKind::unary_operator):
        {
          auto  l = left->to_value();

            switch(element->unop)
            {
              case(Operator('!')): l = !l;break;
              case(Operator('~')): l = ~l;break;
              case(Operator('-')): l = -l;break;
              case(Operator('&')): l = &l;break;
              case(Operator('*')): l = *l;break;
            }


          return std::move(l);
        }
        break;
      case(ElementKind::binary_operator):
        {
          auto  op = element->binop;

          auto  l =  left->to_value();
          auto  r = right->to_value();

            switch(op)
            {
              case(Operator('*')): l = (l*r);break;
              case(Operator('/')): l = (l/r);break;
              case(Operator('%')): l = (l%r);break;

              case(Operator('+')): l = (l+r);break;
              case(Operator('-')): l = (l-r);break;

              case(Operator('<','<')): l = (l<<r);break;
              case(Operator('>','>')): l = (l>>r);break;

              case(Operator('<')    ): l = (l< r);break;
              case(Operator('<','=')): l = (l<=r);break;
              case(Operator('>')    ): l = (l> r);break;
              case(Operator('>','=')): l = (l>=r);break;

              case(Operator('=','=')): l = (l==r);break;
              case(Operator('!','=')): l = (l!=r);break;


              case(Operator('&')): l = (l&r);break;
              case(Operator('|')): l = (l|r);break;
              case(Operator('^')): l = (l^r);break;

              case(Operator('&','&')): l = (l&&r);break;
              case(Operator('|','|')): l = (l&&r);break;

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


          return std::move(l);
        }
    }


  return Value(0LL);
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
      default:
        element.print();
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
              auto  cur_preced = el->binop.get_precedence().number;

                if(unary_operator_stack.size())
                {
                  auto  tail_preced = unary_operator_stack.back()->unop.get_precedence().number;

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

                  auto  tail_preced = tail->binop.get_precedence().number;

                    if(cur_preced <= tail_preced)
                    {
                        if((cur_preced == tail_preced) &&
                           (tail->binop.get_associativity() == Associativity::right_to_left))
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
          default:
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
          default:
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




