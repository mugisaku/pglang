#include"pglang_grammar.hpp"
#include<utility>
#include<memory>




namespace pglang{
namespace grammar{


namespace{


using Result = std::pair<bool,Node*>;

using Iterator = parser::TokenList::const_iterator;


struct
Context
{
  const Book&  book;

  const Definition&  definition;

  Iterator   it;
  Iterator  end;

  Context(const Book&  book_, const Definition&  def):
  book(book_),
  definition(def)
  {}

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
    if(ctx.it == ctx.end)
    {
      return std::make_pair(false,nullptr);
    }


  Node*  nd = new Node(ctx.definition);

  auto  start = ctx.it;

    for(auto&  sym: *grp)
    {
      auto  res = check_symbol(ctx,sym);

        if(res.first)
        {
          nd->append(res.second);

          return std::make_pair(true,nd);
        }

      else
        {
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
    if(ctx.it == ctx.end)
    {
      return std::make_pair(false,nullptr);
    }


  Node*  nd = new Node(ctx.definition);

  auto  start = ctx.it;

    for(auto&  sym: *grp)
    {
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
  auto  nd = new Node(ctx.definition);

    for(;;)
    {
      Result  res(false,nullptr);

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


          return std::make_pair(grp.is_optional(),nd);
        }
    }



  return std::make_pair(true,nd);
}


Result
check_block(const Book&  book, const char*  name, const parser::Block&  blk)
{
  auto  def = book.find(name);

    if(!def)
    {
      printf("定義%sが見つかりませんでした\n",name);

      throw;
    }



    if((def->beginning_character != blk.beginning_character) ||
       (def->ending_character    != blk.ending_character   ))
    {
      return std::make_pair(false,nullptr);
    }


  Context  ctx(book,*def);

  ctx.it  = blk->cbegin();
  ctx.end =   blk->cend();

  auto  nd = new Node(*def);

  auto  res = check_group(ctx,def->get_group());

  nd->append(res.second);

    if(!res.first)
    {
      delete nd;

      return std::make_pair(false,nullptr);
    }


  return std::make_pair(true,nd);
}


Result
check_reference(const Book&  book, const char*  name, Iterator  it, const Iterator  end, Iterator*  itp)
{
  auto  def = book.find(name);

    if(!def)
    {
      printf("定義%sが見つかりませんでした\n",name);

      throw;
    }


  Context  ctx(book,*def);

  auto  base = it;

  ctx.it  =  it;
  ctx.end = end;

  auto  nd = new Node(*def);

  auto  res = check_group(ctx,def->get_group());

  nd->append(res.second);

    if(res.first)
    {
        if(itp)
        {
          *itp = ctx.it;
        }


      return std::make_pair(true,nd);
    }

  else
    {
      delete nd;

      return std::make_pair(false,nullptr);
    }
}


Result
check_symbol(Context&  ctx, const Symbol&  sym)
{
    if(ctx.it == ctx.end)
    {
      return std::make_pair(false,nullptr);
    }


  const parser::Token&  tok = *ctx.it;

  auto&  def = ctx.definition;

  auto  k = tok.get_kind();

if(0)
{
printf("{\n");
tok.print();
printf("\n");
def.print();
printf("\n");
sym.print();
printf("\n}\n");
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
  case(SymbolKind::identifier):
  case(SymbolKind::keyword):
        if((k == parser::TokenKind::identifier) &&
           (tok->s == sym->string))
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
        if(k == parser::TokenKind::block)
        {
          auto  res = check_block(ctx.book,sym->string.data(),tok->blk);

            if(res.first)
            {
              ++ctx.it;

              return res;
            }
        }

      else
        {
          return check_reference(ctx.book,sym->string.data(),ctx.it,ctx.end,&ctx.it);
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




Node*
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

    if(!res.first)
    {
      printf("no matched\n");
    }


  return res.second;
}


}}




