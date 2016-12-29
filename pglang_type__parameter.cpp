#include"pglang_type__parameter.hpp"
#include<cstdlib>




namespace pglang{


Parameter::
Parameter(Type&&  type_, std::string&&  name_, Literal&&  lit):
type(std::move(type_)),
name(std::move(name_)),
literal(std::move(lit)){}


Parameter::
Parameter(std::string&&  name_, Literal&&  lit):
type(Type(lit.get_type())),
name(std::move(name_)),
literal(std::move(lit)){}




const Type&  Parameter::get_type() const{return type;}

const std::string&  Parameter::get_name() const{return name;}

const Literal&  Parameter::get_literal() const{return literal;}

void
Parameter::
set_offset(size_t  v)
{
  auto  asize = type.get_alignment_size();

  offset = ((v+asize-1)/asize*asize);
}


size_t  Parameter::get_offset() const{return offset;}

size_t  Parameter::get_tail_offset() const{return offset+type.get_data_size();}


void
Parameter::
print() const
{
  printf("%s  %s",type.get_name().data(),name.data());

    if(literal)
    {
      printf("=");

      literal.print();
    }
}


}




