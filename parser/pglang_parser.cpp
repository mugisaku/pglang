#include"pglang_parser.hpp"




namespace pglang{
namespace parser{




TokenString::
TokenString(const char*  s)
{
  Stream  st(s);

    for(;;)
    {
      emplace_back(st.get_token());

        if(!back())
        {
          break;
        }
    }
}


}}




