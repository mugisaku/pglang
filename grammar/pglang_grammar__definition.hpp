#ifndef PGLANG_GRAMMAR__DEFINITION_HPP_INCLUDED
#define PGLANG_GRAMMAR__DEFINITION_HPP_INCLUDED


#include<string>
#include"pglang_grammar__group.hpp"


namespace pglang{
namespace grammar{


class
Definition
{
  int   open;
  int  close;

  std::string  name;

  Group  group;

public:
  Definition(std::string&&   name_, int  open_, int  close_, Group&&  grp);

  const std::string&  get_name() const;

  const Group&  get_group() const;

  void  print() const;

};


}}




#endif




