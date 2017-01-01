#include"pglang_grammar__stream.hpp"
#include<cctype>




namespace pglang{
namespace grammar{




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

      Element  e;

        if(c == '{')
        {
          ++pointer;

          e = Element(get_group('{','}'));
        }

      else
        if(c == '(')
        {
          ++pointer;

          e = Element(get_group('(',')'));
        }

      else
        if(c == '[')
        {
          ++pointer;

          e = Element(get_group('[',']'));
        }

      else
        if(c == '%')
        {
          ++pointer;

          e = Element(get_identifier_literal(),ElementKind::keyword);
        }

      else
        if(c == '\"')
        {
          ++pointer;

          auto  op = get_operator();

            if(*pointer != '\"')
            {
              printf("閉じられていません\n");

              throw;
            }


          ++pointer;

          e = Element(std::move(op));
        }

      else
        if(isalpha(c) || (c == '_'))
        {
          auto  s = get_identifier_literal();

          auto  k = ElementKind::reference;

               if(s == "identifier"){k = ElementKind::identifier;}
          else if(s ==    "literal"){k = ElementKind::literal;}

          e = Element(std::move(s),k);
        }

      else
        {
          printf("不明な要素です\n");

          throw;
        }


      grp.append(std::move(e));


      c = *pointer++;

        if(c == close)
        {
          break;
        }


        if((c != ':') ||
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


      skip_spaces();
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




