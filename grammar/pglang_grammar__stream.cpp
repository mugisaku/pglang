#include"pglang_grammar__stream.hpp"
#include"pglang_grammar__symbol.hpp"
#include<cctype>




namespace pglang{
namespace grammar{




Stream::
Stream(const char*  p):
Tag(p)
{
}




Group
Stream::
get_group(int  open, int  close)
{
  Group  grp;

    switch(open)
    {
  case('('): grp.change_kind(GroupKind::regular);break;
  case('['): grp.change_kind(GroupKind::option);break;
  case('{'): grp.change_kind(GroupKind::repetition);break;
  default:;
      printf("グループ種を判定できません\n");

      throw;
    }


  skip_spaces();

    if(*pointer == close)
    {
      ++pointer;

      return std::move(grp);
    }


    for(;;)
    {
      auto  c = *pointer;

      Symbol  sym;

        if(c == '{')
        {
          ++pointer;

          sym = Symbol(get_group('{','}'));
        }

      else
        if(c == '(')
        {
          ++pointer;

          sym = Symbol(get_group('(',')'));
        }

      else
        if(c == '[')
        {
          ++pointer;

          sym = Symbol(get_group('[',']'));
        }

      else
        if(c == '\"')
        {
          ++pointer;

          c = *pointer;

            if(isalpha(c) || (c == '_'))
            {
              sym = Symbol(get_identifier_literal(),SymbolKind::keyword);
            }

          else
            {
              sym = Symbol(get_operator());
            }


            if(*pointer != '\"')
            {
              printf("閉じられていません\n");

              throw;
            }


          ++pointer;
        }

      else
        if(isalpha(c) || (c == '_'))
        {
          auto  s = get_identifier_literal();

          auto  k = SymbolKind::reference;

               if(s == "identifier"){k = SymbolKind::identifier;}
          else if(s ==    "literal"){k = SymbolKind::literal;}
          else if(s ==      "comma"){k = SymbolKind::comma;}
          else if(s ==  "semicolon"){k = SymbolKind::semicolon;}

          sym = Symbol(std::move(s),k);
        }

      else
        {
          printf("不明な要素です\n");

          print();

          throw;
        }


      grp.append(std::move(sym));


      c = *pointer++;

      skip_spaces();

        if(c == close)
        {
          break;
        }


        if((c != ':') &&
           (c != '|'))
        {
          printf("%cは分割子ではありません\n",c);

          throw;
        }


      auto&  sep = grp.get_separator();

        if(!sep.c)
        {
          grp.change_separator(c);
        }

      else
        if(sep.c != c)
        {
          printf("分割子が統一されていません \n");

          throw;
        }
    }


  return std::move(grp);
}


Definition
Stream::
get_definition()
{
  skip_spaces();

  auto  c = *pointer;

    if(isalpha(c) || (c == '_'))
    {
      auto  name = get_identifier_literal();

      int   open = 0;
      int  close = 0;

        if(*pointer == ':')
        {
          ++pointer;

           open = *pointer++;
          close = *pointer++;
        }


      skip_spaces();

        if(*pointer != '=')
        {
          printf("=がありません");

          throw 0;
        }


      ++pointer;

      return Definition(std::move(name),open,close,get_group('(',';'));
    }


  printf("定義はありません\n");

  throw;
}


}}




