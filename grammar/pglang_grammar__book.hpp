#ifndef PGLANG_GRAMMAR__BOOK_HPP_INCLUDED
#define PGLANG_GRAMMAR__BOOK_HPP_INCLUDED


#include<vector>
#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__stream.hpp"


namespace pglang{
namespace grammar{


class
Book
{
  std::vector<Definition>  definition_list;

public:
  Book(Stream&  s);


  const std::vector<Definition>*  operator->() const;

  const Definition*  find(const char*  name) const;

  void  print() const;

};


}}




#endif




