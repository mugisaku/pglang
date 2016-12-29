#ifndef PGLANG_TYPE__ENUM_HPP_INCLUDED
#define PGLANG_TYPE__ENUM_HPP_INCLUDED


#include<string>
#include<vector>
#include"aunique_ptr"




namespace pglang{


class
Enumerator
{
  std::string  name;

  bool  value_defined;

  int  value;

public:
  Enumerator(                            ):                         value_defined(false)          {}
  Enumerator(std::string&&  name_        ): name(std::move(name_)), value_defined(false)          {}
  Enumerator(std::string&&  name_, int  v): name(std::move(name_)), value_defined( true), value(v){}


  const std::string&  get_name() const{return name;}

  int  get_value() const{return value;}

  void  set_value(int  v)
  {
    value = v;

    value_defined = true;
  }

};


class
Enum
{
  std::vector<Enumerator>  enumerator_list;

public:
  Enum();

  void  append(std::string&&  name_             );
  void  append(std::string&&  name_, int   value);

  static constexpr size_t  get_data_size()     {return 4;}
  static constexpr size_t  get_alignment_size(){return 4;}

  void  print() const;

};


}


#endif




