#include"pglang_block.hpp"




namespace pglang{




const std::vector<Stmt>*
Block::
operator->() const
{
  return &stmt_list;
}


void
Block::
append(Stmt&&  stmt)
{
  stmt_list.emplace_back(std::move(stmt));
}


void
Block::
print() const
{
  printf("{");

    for(auto&  stmt: stmt_list)
    {
      printf("  ");

      stmt.print();

      printf("\n");
    }


  printf("}");
}


}




