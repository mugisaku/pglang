#include"pglang_parser.hpp"




using namespace pglang;
using namespace pglang::parser;


void
open(std::string&  buf, const char*  path)
{
  buf.clear();

  auto  f = fopen(path,"rb");

    if(f)
    {
        for(;;)
        {
          auto  c = fgetc(f);

            if(feof(f))
            {
              break;
            }


          buf.push_back(c);
        }


      fclose(f);
    }
}


int
main(int  argc, char**  argv)
{
  --argc;
  ++argv;

  std::string  s;

    while(argc--)
    {
      auto  path = *argv++;

      printf("%s\n",path);

      open(s,path);

      parser::Block  blk(s);


      blk.print();
    }


  return 0;
}




