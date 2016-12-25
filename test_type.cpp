#include"pglang_type.hpp"
#include"pglang_type__book.hpp"
#include"pglang_type__function.hpp"
#include"pglang_expr.hpp"


using namespace pglang;


int
main(int  argc, char**  argv)
{
  Function  fn;

  fn.signature.return_type = Type(Int());
  fn.signature.parameter_list.emplace_back(Type(Int8()),std::string("a"));
  fn.signature.parameter_list.emplace_back(Type(Int16()),std::string("b"));
  fn.signature.parameter_list.emplace_back(Type(UInt8()),std::string("c"));


std::vector<Element>  src({Element(Literal(6LL)),Element(BinaryOperator('+')),Element(Literal(4LL))});


auto  ls = Expr::to_rpn(std::move(src));
auto  res = Expr::create_tree(std::move(ls));

res->print();

res->calculate().print();
/*
  LiteralList  args(0,1.0,2,3.6,LiteralList(2,6,4));

for(auto&  l:args)
{
l.print();
printf("\n");
}
*/

/*
  fn.declare(Type(UInt32()),std::string("x"));
  fn.declare(std::string("y"),Literal(1234));
  fn.declare(std::string("z"),Literal(std::u32string(U"aeiou")));

  fn.execute(args);
*/

  return 0;
}




