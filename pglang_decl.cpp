#include"pglang_decl.hpp"
#include<new>




namespace pglang{






Decl::Decl(): kind(DeclKind::null){}
Decl::Decl(std::string&&  name_, Struct&&    st): name(std::move(name_)), kind(DeclKind::struct_){new(&data) Struct(std::move(st));}
Decl::Decl(std::string&&  name_, Enum&&      en): name(std::move(name_)), kind(DeclKind::enum_){new(&data) Enum(std::move(en));}
Decl::Decl(std::string&&  name_, Union&&     un): name(std::move(name_)), kind(DeclKind::union_){new(&data) Union(std::move(un));}
Decl::Decl(std::string&&  name_, Array&&     ar): name(std::move(name_)), kind(DeclKind::array){new(&data) Array(std::move(ar));}
Decl::Decl(std::string&&  name_, Function&&  fn): name(std::move(name_)), kind(DeclKind::function){new(&data) Function(std::move(fn));}


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

    switch(kind)
    {
  case(DeclKind::struct_):
      new(&data) Struct(std::move(rhs.data.st));
      break;
  case(DeclKind::enum_):
      new(&data) Enum(std::move(rhs.data.en));
      break;
  case(DeclKind::union_):
      new(&data) Union(std::move(rhs.data.un));
      break;
  case(DeclKind::array):
      new(&data) Array(std::move(rhs.data.ar));
      break;
  case(DeclKind::function):
      new(&data) Function(std::move(rhs.data.fn));
      break;
    }


  return *this;
}


Decl&
Decl::
operator=(const Decl&  rhs)
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(DeclKind::struct_):
      new(&data) Struct(rhs.data.st);
      break;
  case(DeclKind::enum_):
      new(&data) Enum(rhs.data.en);
      break;
  case(DeclKind::union_):
      new(&data) Union(rhs.data.un);
      break;
  case(DeclKind::array):
      new(&data) Array(rhs.data.ar);
      break;
  case(DeclKind::function):
      new(&data) Function(rhs.data.fn);
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


void
Decl::
print() const
{
}


}




