#ifndef PGLANG_PARSER__BLOCK_HPP_INCLUDED
#define PGLANG_PARSER__BLOCK_HPP_INCLUDED


#include<vector>
#include<string>


#ifndef report
#define report  printf("[report in %s] %d %s\n",__FILE__,__LINE__,__func__);
#endif


namespace pglang{
namespace parser{


struct Token;
struct Stream;


class
Block: public std::vector<Token>
{
  char  opening_c;
  char  closing_c;

public:
  Block(                     );
  Block(const std::string&  s);

  bool  build(Stream&  st, char  opening=0);

  void  print(int  indent=0) const;

};


}}




#endif




