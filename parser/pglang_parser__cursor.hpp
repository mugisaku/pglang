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
  void  newline();

  void  skip_spaces();

  void  print() const;

  static void  print_character(int  c);
  static void  print_string(const std::string&  s);

};


}}




#endif




