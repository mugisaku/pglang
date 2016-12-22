#include"pglang_type__function.hpp"
#include"pglang_type.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_vm__context.hpp"
#include<cstdlib>




namespace pglang{




Struct
Function::
make_stack_struct() const
{
  Struct  st;

    for(auto&  vardecl: vardecl_list)
    {
      st.append(Type(vardecl.type),std::string(vardecl.name));
    }


  st.append(Type(UInt32()),std::string("previous_bp"));
  st.append(Type(UInt32()),std::string("previous_sp"));
  st.append(Type(UInt32()),std::string("return_address"));

    for(auto&  p: signature.parameter_list)
    {
      st.append(Type(p.type),std::string(p.name));
    }


  st.append(Type(signature.return_type),std::string("return_value"));


  return std::move(st);
}


Literal
Function::
execute(const ArgumentList&  args)
{
  auto  st = make_stack_struct();

  st.print();

  vm::Memory  mem(1024);

  vm::Context  ctx(mem,st,args);

  return Literal();
}


void
Function::
declare(Type&&  type, std::string&&  name, Literal&&  lit)
{
  vardecl_list.emplace_back(std::move(type),std::move(name),std::move(lit));
}


void
Function::
declare(std::string&&  name, Literal&&  lit)
{
  vardecl_list.emplace_back(std::move(name),std::move(lit));
}


void
Function::
print() const
{
}


}




