#include"pglang_grammar__book.hpp"
#include"pglang_grammar__element.hpp"




namespace pglang{
namespace grammar{




Book::
Book(Stream&  s)
{
    while(s)
    {
      auto  def = s.get_definition();

      definition_list.emplace_back(std::move(def));
    }
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




