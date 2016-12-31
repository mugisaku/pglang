#ifndef PGLANG_PARSER__UNICODE_HPP
#define PGLANG_PARSER__UNICODE_HPP


#include<cstdint>
#include<string>


namespace pglang{
namespace parser{


struct
UTF8Chunk
{
  char  data[4];

  UTF8Chunk(char16_t  c);

  UTF8Chunk&  operator=(char16_t  c);

};


size_t  get_utf8_byte_number(int  c);

std::u16string  to_u16string(const std::string&  src);


}}


#endif




