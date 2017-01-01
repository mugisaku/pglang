#ifndef PGLANG_GRAMMAR__STREAM_HPP_INCLUDED
#define PGLANG_GRAMMAR__STREAM_HPP_INCLUDED


#include"pglang_parser__tag.hpp"
#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__group.hpp"
#include"pglang_grammar__element.hpp"


namespace pglang{
namespace grammar{


class
Stream: public parser::Tag
{
  Group  get_group(int  open, int  close);

public:
  Stream(const char*  p);

  Definition  get_definition();

};


}}




#endif




