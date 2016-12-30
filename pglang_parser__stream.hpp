#ifndef PGLANG_PARSER__STREAM_HPP_INCLUDED
#define PGLANG_PARSER__STREAM_HPP_INCLUDED


#include<cstdint>
#include<string>
#include"pglang_expr__operator.hpp"
#include"pglang_parser__token.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


class
Stream: public Tag
{
  std::string  get_string_literal();
  std::string  get_identifier_literal();
  uint64_t     get_character_literal();
  uint64_t  get_binary_integer_literal();
  Operator  get_operator();

  bool  get_binary_number(int&  i);
  bool  get_octet_number(int&  i);
  bool  get_decimal_number(int&  i);
  bool  get_hexadecimal_number(int&  i);

  char32_t  get_escchar();
  char16_t  get_unichar16();
  char32_t  get_unichar32();

public:
  Stream(const char*  p);

  operator bool() const;

  char  operator*() const;

  void  skip_spaces();

  void  advance();

  Token  get_token();

};


}}




#endif




