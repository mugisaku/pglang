#include"pglang_grammar__book.hpp"
#include"pglang_grammar__symbol.hpp"




namespace pglang{
namespace grammar{




Book::
Book(Stream&  s)
{
    while(s)
    {
      definition_list.emplace_back(s.get_definition());
    }
}




const std::vector<Definition>*  Book::operator->() const{return &definition_list;}


const Definition*
Book::
find(const char*  name) const
{
    for(auto&  def: definition_list)
    {
        if(def.get_name() == name)
        {
          return &def;
        }
    }


  return nullptr;
}


void
Book::
print() const
{
    for(auto&  def: definition_list)
    {
      def.print();

      printf("\n");
    }
}


}}




