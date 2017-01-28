#ifndef PGLANG_PARSER_HPP_INCLUDED
#define PGLANG_PARSER_HPP_INCLUDED


#include"pglang_parser__stream.hpp"
#include"pglang_parser__token.hpp"
#include"pglang_parser__unicode.hpp"
#include"pglang_parser__tag.hpp"
#include<vector>


namespace pglang{
namespace parser{


class
TokenString: public std::vector<Token>
{
public:
  TokenString(const char*  s);

};


}}


#endif




