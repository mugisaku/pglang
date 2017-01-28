#ifndef PGLANG_GRAMMAR__NODE_HPP_INCLUDED
#define PGLANG_GRAMMAR__NODE_HPP_INCLUDED


#include<vector>
#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__book.hpp"
#include"pglang_grammar__symbol.hpp"
#include"pglang_parser__token.hpp"


namespace pglang{
namespace grammar{


using NodeList = std::vector<Node*>;


class
Node
{
  const parser::Token*  token;

  NodeList  children;
  
public:
  const Definition&  definition;

  const bool  keyword_flag;

  Node(const Definition&  def, const parser::Token*  tok=nullptr, bool  kw=false);
 ~Node();

  const NodeList&  operator*() const;
  const NodeList*  operator->() const;

  bool  operator==(const char*  name) const;

  size_t  check(const Book&  book);

  void  append(Node*  child);

  const parser::Token&  get_token() const;

  void  print() const;

  class Reader{
          NodeList::const_iterator  pointer    ;
    const NodeList::const_iterator  pointer_end;

  public:
    Reader(const Node&  src):
    pointer(src->cbegin()),
    pointer_end(src->cend()){}

    operator bool() const{return pointer != pointer_end;}

    const Node&  operator*() const{return **pointer;}

    void  advance()
    {
        if(pointer != pointer_end)
        {
          ++pointer;
        }
    }

  };


  Reader  reader() const;

};


}}




#endif




