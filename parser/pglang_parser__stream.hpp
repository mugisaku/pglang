#ifndef PGLANG_PARSER__STREAM_HPP_INCLUDED
#define PGLANG_PARSER__STREAM_HPP_INCLUDED


#include"pglang_parser__cursor.hpp"
#include"pglang_parser__token.hpp"


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


struct invalid_character{};
struct invalid_string{};
struct invalid_unicode{};
struct invalid_number{};
struct irregular_block{};


class
Stream: public Cursor
{
  char32_t  get_escchar();
  char16_t  get_unichar16();
  char32_t  get_unichar32();

  uint64_t  get_binary_integer();
  uint64_t  get_octet_integer();
  uint64_t  get_decimal_integer();
  uint64_t  get_hexadecimal_integer();

  bool  get_binary_number(int&  i);
  bool  get_octet_number(int&  i);
  bool  get_decimal_number(int&  i);
  bool  get_hexadecimal_number(int&  i);

  Token  get_number_token();

  Operator  get_operator();

  std::string  get_string();
  std::string  get_identifier();

  uint64_t  get_character();

  Token  internal__get_block_token();
  Token  internal__get_nonblock_token();

public:
  Stream(const std::string&  s);

  Token  get_token();

};


}}




#endif




