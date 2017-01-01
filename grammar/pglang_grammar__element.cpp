#include"pglang_grammar__element.hpp"
#include"pglang_grammar__group.hpp"
#include<new>




namespace pglang{
namespace grammar{




Element::Element():kind(ElementKind::null){}
Element::Element(std::string&&  s, ElementKind  k): kind(k){new(&data.string) std::string(std::move(s));}
Element::Element(Group&&  grp): kind(ElementKind::group){new(&data.group) Group(std::move(grp));}
Element::Element(Operator&&  op): kind(ElementKind::operator_){data.operator_ = op;}
Element::Element(      Element&&  rhs) noexcept: kind(ElementKind::null){*this = std::move(rhs);}
Element::Element(const Element&   rhs) noexcept: kind(ElementKind::null){*this = rhs;}
Element::~Element(){clear();}




Element&
Element::
operator=(Element&&  rhs) noexcept
{
  clear();

  kind = rhs.kind                    ;
         rhs.kind = ElementKind::null;

    switch(kind)
    {
  case(ElementKind::null):
  case(ElementKind::literal):
  case(ElementKind::identifier):
      break;
  case(ElementKind::keyword):
  case(ElementKind::reference):
      new(&data.string) std::string(std::move(rhs.data.string));
      break;
  case(ElementKind::group):
      new(&data.group) Group(std::move(rhs.data.group));
      break;
  case(ElementKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
    }


  return *this;
}


Element&
Element::
operator=(const Element&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ElementKind::null):
  case(ElementKind::literal):
  case(ElementKind::identifier):
      break;
  case(ElementKind::keyword):
  case(ElementKind::reference):
      new(&data.string) std::string(rhs.data.string);
      break;
  case(ElementKind::group):
      new(&data.group) Group(rhs.data.group);
      break;
  case(ElementKind::operator_):
      data.operator_ = rhs.data.operator_;
      break;
    }


  return *this;
}


const ElementData*  Element::operator->() const{return &data;}




void
Element::
clear()
{
    switch(kind)
    {
  case(ElementKind::null):
  case(ElementKind::literal):
  case(ElementKind::identifier):
      break;
  case(ElementKind::keyword):
  case(ElementKind::reference):
      data.string.~basic_string();
      break;
  case(ElementKind::group):
      data.group.~Group();
      break;
  case(ElementKind::operator_):
      break;
    }


  kind = ElementKind::null;
}


ElementKind  Element::get_kind() const{return kind;}


void
Element::
print() const
{
    switch(kind)
    {
  case(ElementKind::literal):    printf("literal");break;
  case(ElementKind::identifier): printf("identifier");break;
  case(ElementKind::keyword):    printf("%%%s",data.string.data());break;
  case(ElementKind::operator_):  printf("\"%s\"",data.operator_.codes);break;
  case(ElementKind::reference):  printf("%s",data.string.data());break;
  case(ElementKind::group): data.group.print();break;
    }
}


}}




