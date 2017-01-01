#ifndef PGLANG_PARSER__TAG_HPP_INCLUDED
#define PGLANG_PARSER__TAG_HPP_INCLUDED


#include<cstddef>
#include<string>
#include"pglang_expr__operator.hpp"


namespace pglang{
namespace parser{


class
Tag
{
protected:
  const char*  base_pointer;
  const char*       pointer;

  size_t   row_number;

  std::string  get_identifier_literal();

  Operator  get_operator();

public:
  Tag(const char*  p=nullptr);


  operator bool() const;

  char  operator*() const;

  void  skip_spaces();

  void  advance();

  void  print() const;

};


bool  isoperator(int  c);


}}




#endif




