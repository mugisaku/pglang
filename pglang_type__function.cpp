#include"pglang_type__function.hpp"
#include"pglang_type.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_vm__context.hpp"
#include<cstdlib>




namespace pglang{


Literal
Function::
execute(const ArgumentList&  args)
{
  Struct  st;

  st.append(Type(UInt32()),std::string("previous_bp"));
  st.append(Type(UInt32()),std::string("previous_sp"));
  st.append(Type(UInt32()),std::string("return_address"));

    for(auto&  p: signature.parameter_list)
    {
      st.append(Type(p.type),std::string(p.name));
    }


  st.append(Type(signature.return_type),std::string("return_value"));

  st.print();

    if(args.size() != signature.parameter_list.size())
    {
      printf("仮引数と実引数の個数が一致しません\n");

      throw;
    }


  vm::Memory  mem(1024);

  vm::Context  ctx(mem,st,args);

  return Literal();
}


void
Function::
print() const
{
}


}




