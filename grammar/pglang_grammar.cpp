#include"pglang_grammar.hpp"
#include<vector>




namespace pglang{
namespace grammar{


namespace{


using Iterator = parser::TokenList::const_iterator;


struct
Context
{
  const Book&  book;

  std::vector<const Definition*>  definition_stack;

  Iterator   it;
  Iterator  end;

  Context(const Book&  book_, const Definition&  def):
  book(book_)
  {

    definition_stack.emplace_back(&def);
  }

  operator bool() const{return it != end;}

  const Definition&  operator*() const{return *definition_stack.back();}

};




bool
isliteral(const parser::TokenKind  k)
{
  return((k == parser::TokenKind::integer) ||
         (k == parser::TokenKind::floating_point_number) ||
         (k == parser::TokenKind::string) ||
         (k == parser::TokenKind::u16string) ||
         (k == parser::TokenKind::u32string) ||
         (k == parser::TokenKind::nullptr_) ||
         (k == parser::TokenKind::true_) ||
         (k == parser::TokenKind::false_));
}


Result  check_symbol(Context&  ctx, const Symbol&  sym);


Result
check_whether_it_matches_one(Context&  ctx, const Group&  grp)
{
  Node*  nd = new Node(*ctx);

  auto  start = ctx.it;

    for(auto&  sym: *grp)
    {
        if(!ctx)
        {
          break;
        }


      auto  point = ctx.it;

      auto  res = check_symbol(ctx,sym);

        if(res.first)
        {
          nd->append(res.second);

          return std::make_pair(true,nd);
        }

      else
        {
          ctx.it = point;

          delete res.second;
        }
    }


  ctx.it = start;

  delete nd;

  return std::make_pair(false,nullptr);
}


Result
check_whether_it_matches_all(Context&  ctx, const Group&  grp)
{
  Node*  nd = new Node(*ctx);

  auto  start = ctx.it;

    for(auto&  sym: *grp)
    {
        if(!ctx)
        {
          ctx.it = start;

          delete nd;

          return std::make_pair(false,nullptr);
        }


      Result  res = check_symbol(ctx,sym);

      nd->append(res.second);

        if(!res.first)
        {
          ctx.it = start;

          delete nd;

          return std::make_pair(false,nullptr);
        }
    }


  return std::make_pair(true,nd);
}


Result
check_group(Context&  ctx, const Group&  grp)
{
  auto  nd = new Node(*ctx);

  bool  b;

  auto  start = ctx.it;

    for(;;)
    {
      Result  res;

        if(grp.get_separator().c == '|')
        {
          res = check_whether_it_matches_one(ctx,grp);
        }

      else
        {
          res = check_whether_it_matches_all(ctx,grp);
        }


        if(res.first)
        {
          b = true;

          nd->append(res.second);

            if(!grp.is_repetitional())
            {
              break;
            }
        }

      else
        {
            if((*nd)->empty())
            {
              delete nd          ;
                     nd = nullptr;
            }


          b = grp.is_optional();

          break;
        }
    }


    if(!b)
    {
      ctx.it = start;
    }


  return std::make_pair(b,nd);
}


Result
check_symbol(Context&  ctx, const Symbol&  sym)
{
  const parser::Token&  tok = *ctx.it;

  auto&  def = *ctx;

  auto  k = tok.get_kind();

if(0)
{
printf("<test>\n  token = ");
tok.print();
printf("\n  definition = ");
def.print();
printf("\n  symbol = ");
sym.print();
printf("\n</test>\n");
}
    switch(sym.get_kind())
    {
  case(SymbolKind::literal):
        if(isliteral(k))
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok));
        }
      break;
  case(SymbolKind::keyword):
        if((k == parser::TokenKind::identifier) &&
           (tok->s == sym->string))
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok,true));
        }
      break;
  case(SymbolKind::identifier):
        if(k == parser::TokenKind::identifier)
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok));
        }
      break;
  case(SymbolKind::operator_):
        if((k == parser::TokenKind::operator_) &&
           (tok->operator_ == sym->operator_))
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok));
        }
      break;
  case(SymbolKind::reference):
    {
      auto  rdef = ctx.book.find(sym->string.data());

        if(rdef)
        {
          ctx.definition_stack.emplace_back(rdef);

            if(rdef->beginning_character)
            {
                if(k == parser::TokenKind::block)
                {
                    if((rdef->beginning_character == tok->blk.beginning_character) &&
                       (rdef->ending_character    == tok->blk.ending_character   ))
                    {
                      ++ctx.it;

                      return std::make_pair(true,new Node(*rdef,&tok));
                    }
                }
            }

          else
            {
              return check_group(ctx,rdef->get_group());
            }
        }

      else
        {
          printf("定義%sが見つかりませんでした\n",sym->string.data());

          throw;
        }
    }
      break;
  case(SymbolKind::group):
      return check_group(ctx,sym->group);
      break;
  case(SymbolKind::semicolon):
        if(k == parser::TokenKind::semicolon)
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok));
        }
      break;
  case(SymbolKind::comma):
        if(k == parser::TokenKind::comma)
        {
          ++ctx.it;

          return std::make_pair(true,new Node(def,&tok));
        }
      break;
  default:
      printf("本来到達不能");

      throw;
    }


  return std::make_pair(false,nullptr);
}




}




Result
start_check(const Book&  book, const char*  name, const parser::Block&  blk)
{
  auto  def = book.find(name);

    if(!def)
    {
      printf("定義%sが見つかりませんでした\n",name);

      throw;
    }


  Context  ctx(book,*def);

  ctx.it  = blk->cbegin();
  ctx.end =   blk->cend();

  auto  res = check_group(ctx,def->get_group());

    if(ctx.it != ctx.end)
    {
      printf("%s:未定義の要素が現れました\n",name);

      ctx.it->get_tag().print();

      printf("\n");
    }


  return res;
}


}}




