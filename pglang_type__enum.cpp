#include"pglang_type__enum.hpp"
#include"pglang_type.hpp"




namespace pglang{


Enum::
Enum()
{
}




void
Enum::
append(std::string&&  name_)
{
    if(enumerator_list.size())
    {
      int  v = enumerator_list.back().get_value()+1;

      enumerator_list.emplace_back(std::move(name_),v);
    }

  else
    {
      enumerator_list.emplace_back(std::move(name_),0);
    }
}


void
Enum::
append(std::string&&  name_, int   value)
{
  enumerator_list.emplace_back(std::move(name_),value);
}




void
Enum::
print() const
{
    for(auto&  en: enumerator_list)
    {
      printf("%s = %d;\n",en.get_name().data(),en.get_value());
    }
}


}




