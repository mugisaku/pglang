#include"pglang_grammar__node.hpp"
#include"pglang_grammar.hpp"




namespace pglang{
namespace grammar{




Node::
Node(const Definition&  def, const parser::Token*  tok, bool  kw):
definition(def),
keyword_flag(kw),
token(tok)
{
}


Node::
~Node()
{
    for(auto  child: children)
    {
      delete child;
    }
}




const std::vector<Node*>*  Node::operator->() const{return &children;}

void
Node::
append(Node*  child)
{
    if(child)
    {
        if(token)
        {
          printf("葉ノードに子ノードを付けようとしました\n");

          print();

          printf("\n");

          child->print();

          printf("\n");

          throw;
        }


      children.emplace_back(child);
    }
}


size_t
Node::
check(const Book&  book)
{
  size_t  n = 0;

    if(token && (token->get_kind() == parser::TokenKind::block))
    {
      auto  name = definition.get_name().data();

      auto&  blk = (*token)->blk;

      auto  res = start_check(book,name,blk);

        if(res.first)
        {
          token = nullptr;

          append(res.second);
        }


      n = 1;
    }

  else
    {
        for(auto  child: children)
        {
          n += child->check(book);
        }
    }


  return n;
}


void
Node::
print() const
{
    if(token)
    {
      printf("[%s]",definition.get_name().data());

        if(keyword_flag)
        {
          printf("KEYWORD");
        }


      printf("  ");

        if(token->get_kind() == parser::TokenKind::block)
        {
          printf("%c--",(*token)->blk.beginning_character);
          printf("%c",(*token)->blk.ending_character);
        }

      else
        {
          token->print();
        }


      printf("\n");
    }

  else
    {
        for(auto  child: children)
        {
          child->print();
        }
    }
}


}}




