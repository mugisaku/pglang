#ifndef PGLANG_ABSYN__DEFINITION_HPP_INCLUDED
#define PGLANG_ABSYN__DEFINITION_HPP_INCLUDED


#include<string>
#include"pglang_absyn__group.hpp"


namespace pglang{
namespace absyn{


class
Definition: public Group
{
  std::string  name;

public:

  void  print(int  indent=0) const;

};


}}




#endif




