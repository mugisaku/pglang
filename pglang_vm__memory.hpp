#ifndef PGLANG_VM__MEMORY_HPP_INCLUDED
#define PGLANG_VM__MEMORY_HPP_INCLUDED


#include<cstdint>
#include<cstddef>


namespace pglang{
namespace vm{


class
Memory
{
  size_t  size;

  uint8_t*  array;

public:
   Memory(size_t  size_);
   Memory(      Memory&&  rhs) noexcept;
   Memory(const Memory&   rhs)         ;
  ~Memory();

  Memory&  operator=(      Memory&&  rhs) noexcept;
  Memory&  operator=(const Memory&   rhs)         ;

  size_t  get_size() const;

  void  resize(size_t  new_size);

  int  get8(  int  ptr) const;
  int  get8u( int  ptr) const;
  int  get16( int  ptr) const;
  int  get16u(int  ptr) const;
  int  get32( int  ptr) const;

  void  put8( int  ptr, int  val);
  void  put16(int  ptr, int  val);
  void  put32(int  ptr, int  val);

  void  fill(int  v=0);


};


}}




#endif




