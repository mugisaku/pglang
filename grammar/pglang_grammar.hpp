#ifndef PGLANG_GRAMMAR_HPP_INCLUDED
#define PGLANG_GRAMMAR_HPP_INCLUDED


#include"pglang_grammar__book.hpp"
#include"pglang_grammar__node.hpp"
#include"pglang_grammar__symbol.hpp"
#include"pglang_grammar__group.hpp"
#include"pglang_grammar__definition.hpp"
#include"pglang_grammar__stream.hpp"


namespace pglang{
namespace grammar{


using Result = std::pair<bool,Node*>;


Result  start_check(const Book&  book, const char*  name, const parser::Block&  blk);


}}


#endif




