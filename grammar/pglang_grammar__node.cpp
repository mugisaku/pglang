#include"pglang_grammar__node.hpp"




namespace pglang{
namespace grammar{




Node::
Node(const Definition&  def, const parser::Token*  tok):
definition(def),
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


void
Node::
print() const
{
    if(token)
    {
      definition.print();

      printf("::");

      token->print();

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




