#include"pglang_parser.hpp"
#include"pglang_grammar.hpp"




using namespace pglang;


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
  std::string  book_s;
  std::string  code_s;

  open(book_s,"test_grammar.book.txt");
  open(code_s,"test_grammar.code.txt");

  parser::Stream   pst(code_s.data());
  grammar::Stream  gst(book_s.data());

  parser::Block  pblk(pst);

  grammar::Book  book(gst);

  auto  res = grammar::start_check(book,"object",pblk);

  printf("book{\n");

  book.print();

  printf("}\n\n");

    if(res.first)
    {
      printf("**\n");

        while(res.second->check(book))
        {
        }


      res.second->print();

      printf("**\n");
    }


  return 0;
}




