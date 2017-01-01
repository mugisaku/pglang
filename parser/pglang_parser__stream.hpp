#ifndef PGLANG_PARSER__STREAM_HPP_INCLUDED
#define PGLANG_PARSER__STREAM_HPP_INCLUDED


#include<cstdint>
#include<string>
#include"pglang_parser__token.hpp"
#include"pglang_expr__operator.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


struct invalid_character_literal{};
struct invalid_string_literal{};
struct invalid_unicode_literal{};
struct invalid_number_literal{};


class
Stream: public Tag
{
  std::string  get_string_literal();
  uint64_t     get_character_literal();

  char32_t  get_escchar();
  char16_t  get_unichar16();
  char32_t  get_unichar32();

  uint64_t  get_binary_integer_literal();
  uint64_t  get_octet_integer_literal();
  uint64_t  get_decimal_integer_literal();
  uint64_t  get_hexadecimal_integer_literal();

  bool  get_binary_number(int&  i);
  bool  get_octet_number(int&  i);
  bool  get_decimal_number(int&  i);
  bool  get_hexadecimal_number(int&  i);

public:
  Stream(const char*  p);

  Token  get_token();

};


}}




#endif




