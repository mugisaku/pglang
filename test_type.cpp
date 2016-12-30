#include"pglang_type.hpp"
#include"pglang_type__function.hpp"
#include"pglang_expr.hpp"
#include"pglang_block.hpp"
#include"pglang_parser__block.hpp"
#include"pglang_parser__stream.hpp"
#include"pglang_parser__token.hpp"




using namespace pglang;


int
main(int  argc, char**  argv)
{
/*
  auto  sig = Signature(Type(Int()));

  sig.append_parameter(Type( Int8()),std::string("a"));
  sig.append_parameter(Type(Int16()),std::string("b"));
  sig.append_parameter(Type(UInt8()),std::string("c"));

  Function  fn(std::move(sig));


std::vector<Element>  src({Element(Literal(6LL)),Element(BinaryOperator('+')),Element(Literal(4LL))});


auto  ls = Expr::to_rpn(std::move(src));
auto  res = Expr::create_tree(std::move(ls));

res->print();

res->to_value(nullptr).print();
*/


parser::Stream  s(";{a; b} -5+67.0788:{;c ;}");

parser::Block  blk(s);

blk.print();


printf("\n");


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




