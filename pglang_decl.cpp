#include"pglang_decl.hpp"
#include"pglang_block.hpp"
#include"pglang_type.hpp"
#include<new>




namespace pglang{






Decl::Decl(): kind(DeclKind::null){}
Decl::Decl(std::string&&  name_, Struct&&    st): name(std::move(name_)), kind(DeclKind::struct_){new(&data.st) Struct(std::move(st));}
Decl::Decl(std::string&&  name_, Enum&&      en): name(std::move(name_)), kind(DeclKind::enum_){new(&data.en) Enum(std::move(en));}
Decl::Decl(std::string&&  name_, Union&&     un): name(std::move(name_)), kind(DeclKind::union_){new(&data.un) Union(std::move(un));}
Decl::Decl(std::string&&  name_, Array&&     ar): name(std::move(name_)), kind(DeclKind::array){new(&data.ar) Array(std::move(ar));}
Decl::Decl(std::string&&  name_, Function&&  fn): name(std::move(name_)), kind(DeclKind::function){new(&data.fn) Function(std::move(fn));}


Decl::
Decl(Decl&&  rhs) noexcept:
kind(DeclKind::null)
{
  *this = std::move(rhs);
}


Decl::
Decl(const Decl&   rhs):
kind(DeclKind::null)
{
  *this = rhs;
}


Decl::~Decl()
{
  clear();
}




Decl&
Decl::
operator=(Decl&&  rhs)
{
  clear();

  std::swap(kind,rhs.kind);
  std::swap(defined,rhs.defined);

    switch(kind)
    {
  case(DeclKind::struct_):
      new(&data.st) Struct(std::move(rhs.data.st));
      break;
  case(DeclKind::enum_):
      new(&data.en) Enum(std::move(rhs.data.en));
      break;
  case(DeclKind::union_):
      new(&data.un) Union(std::move(rhs.data.un));
      break;
  case(DeclKind::array):
      new(&data.ar) Array(std::move(rhs.data.ar));
      break;
  case(DeclKind::function):
      new(&data.fn) Function(std::move(rhs.data.fn));
      break;
    }


  return *this;
}


Decl&
Decl::
operator=(const Decl&  rhs)
{
  clear();

  kind    = rhs.kind;
  defined = rhs.defined;

    switch(kind)
    {
  case(DeclKind::struct_):
      new(&data.st) Struct(rhs.data.st);
      break;
  case(DeclKind::enum_):
      new(&data.en) Enum(rhs.data.en);
      break;
  case(DeclKind::union_):
      new(&data.un) Union(rhs.data.un);
      break;
  case(DeclKind::array):
      new(&data.ar) Array(rhs.data.ar);
      break;
  case(DeclKind::function):
      new(&data.fn) Function(rhs.data.fn);
      break;
    }


  return *this;
}


const DeclData*
Decl::
operator->() const
{
  return &data;
}


void
Decl::
clear()
{
    switch(kind)
    {
  case(DeclKind::struct_):
      data.st.~Struct();
      break;
  case(DeclKind::enum_):
      data.en.~Enum();
      break;
  case(DeclKind::union_):
      data.un.~Union();
      break;
  case(DeclKind::array):
      data.ar.~Array();
      break;
  case(DeclKind::function):
      data.fn.~Function();
      break;
    }


  kind = DeclKind::null;
  defined = false;
}


const std::string&
Decl::
get_name() const
{
  return name;
}


DeclKind
Decl::
get_kind() const
{
  return kind;
}


bool
Decl::
is_defined() const
{
  return defined;
}


size_t
Decl::
get_data_size() const
{
    switch(kind)
    {
  case(DeclKind::struct_):
      return data.st.get_data_size();
      break;
  case(DeclKind::enum_):
      return data.en.get_data_size();
      break;
  case(DeclKind::union_):
      return data.un.get_data_size();
      break;
  case(DeclKind::array):
      return data.ar.get_data_size();
      break;
  case(DeclKind::function):
      return GenericPtr::get_data_size();
      break;
    }
}


size_t
Decl::
get_alignment_size() const
{
    switch(kind)
    {
  case(DeclKind::struct_):
      return data.st.get_alignment_size();
      break;
  case(DeclKind::enum_):
      return data.en.get_alignment_size();
      break;
  case(DeclKind::union_):
      return data.un.get_alignment_size();
      break;
  case(DeclKind::array):
      return data.ar.get_alignment_size();
      break;
  case(DeclKind::function):
      return GenericPtr::get_alignment_size();
      break;
    }
}


void
Decl::
print() const
{
    switch(kind)
    {
  case(DeclKind::struct_):
      data.st.print();
      break;
  case(DeclKind::enum_):
      data.en.print();
      break;
  case(DeclKind::union_):
      data.un.print();
      break;
  case(DeclKind::array):
      data.ar.print();
      break;
  case(DeclKind::function):
      data.fn.print();
      break;
    }
}


}




