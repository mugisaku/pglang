#include"pglang_type__function.hpp"
#include"pglang_type.hpp"
#include"pglang_type__struct.hpp"
#include"pglang_vm__context.hpp"
#include<cstdlib>




namespace pglang{




namespace{


Struct
make_stack_struct(const Signature&  sig, const std::vector<Parameter>&  vardecl_list)
{
  Struct  st;

    for(auto&  vardecl: vardecl_list)
    {
      st.append(Type(vardecl.type),std::string(vardecl.name));
    }


  st.append(Type(UInt32()),std::string("previous_bp"));
  st.append(Type(UInt32()),std::string("previous_sp"));
  st.append(Type(UInt32()),std::string("return_address"));

    for(auto&  p: sig.parameter_list)
    {
      st.append(Type(p.type),std::string(p.name));
    }


  st.append(Type(sig.return_type),std::string("return_value"));


  return std::move(st);
}


Struct
make_literaldata_struct(const std::vector<Parameter>&  vardecl_list)
{
  Struct  st;

    for(auto&  vardecl: vardecl_list)
    {
        switch(vardecl.literal.get_kind())
        {
      case(LiteralKind::string):
      case(LiteralKind::u16string):
      case(LiteralKind::u32string):
      case(LiteralKind::array):
          st.append(Type(vardecl.type),std::string(vardecl.name),Literal(vardecl.literal));
          break;
      default:;
        }
    }


  return std::move(st);
}
}


Literal
Function::
execute(const ArgumentList&  args)
{
  signature.print();

  auto  stst = make_stack_struct(signature,vardecl_list);
  auto  ldst = make_literaldata_struct(vardecl_list);

  printf("\nstack{\n");

  stst.print();

  printf("\n}\n\n");

  printf("literaldata{\n");

  ldst.print();

  printf("\n}\n\n");

    if(binary)
    {
      vm::Memory  mem(1024*1024);

/*
        for(auto&  m: ldst.member_list)
        {
          auto&  lit = m.literal;

          lit.write(mem.get_pointer(m.offset));
        }
*/


      vm::Context  ctx(mem,stst,args);
    }


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




