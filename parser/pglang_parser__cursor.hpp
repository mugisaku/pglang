#ifndef PGLANG_PARSER__CURSOR_HPP_INCLUDED
#define PGLANG_PARSER__CURSOR_HPP_INCLUDED


#include<cstddef>
#include<string>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


class
Cursor
{
protected:
  const char*  base_pointer;
  const char*       pointer;

  size_t   row_number;

public:
  Cursor(                     );
  Cursor(const std::string&  s);

  char  operator*() const;

  void  advance();

  void  print() const;

  static void  print_character(int  c, int  n=1);
  static void  print_character_literal(int  c);
  static void  print_string_literal(const std::string&  s);

};


}}




#endif




