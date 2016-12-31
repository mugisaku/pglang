#ifndef PGLANG_EXPR__INITIALIZER_HPP_INCLUDED
#define PGLANG_EXPR__INITIALIZER_HPP_INCLUDED


#include<cstdint>
#include<string>
#include<vector>




namespace pglang{




enum class
InitializerKind
{
  null,

  expression,
  initializer_list,

};


struct Expr;
struct Initializer;


using InitializerList = std::vector<Initializer>;


union
InitializerData
{
  Expr*             expr;
  InitializerList*  list;

   InitializerData(){}
  ~InitializerData(){}

};


class
Initializer
{
  InitializerKind  kind;
  InitializerData  data;

public:
  Initializer();
  Initializer(Expr*  expr);
  Initializer(InitializerList*  list);
  Initializer(      Initializer&&  rhs) noexcept;
  Initializer(const Initializer&   rhs);
  ~Initializer();

  Initializer&  operator=(      Initializer&&  rhs) noexcept;
  Initializer&  operator=(const Initializer&   rhs)         ;

  operator bool() const;

  InitializerKind  get_kind() const;
  const InitializerData*  operator->() const;

  void  clear();
  void  print() const;

};


}


#endif




