#ifndef PGLANG_GRAMMAR__DEFINITION_HPP_INCLUDED
#define PGLANG_GRAMMAR__DEFINITION_HPP_INCLUDED


#include<string>
#include"pglang_grammar__group.hpp"
#include"pglang_parser__block.hpp"


namespace pglang{
namespace grammar{


struct Book;
struct Node;


class
Definition
{
  std::string  name;

  Group  group;

public:
  const int   beginning_character;
  const int      ending_character;

  Definition(std::string&&   name_, int  begin_, int  end_, Group&&  grp);

  const std::string&  get_name() const;

  const Group&  get_group() const;

  void  print() const;

};


}}




#endif




