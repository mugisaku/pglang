#include"pglang_vm__memory.hpp"
#include<cstring>
#include<utility>




namespace pglang{
namespace vm{




Memory::
Memory(size_t  size_):
size(0),
array(nullptr)
{
  resize(size_);
}


Memory::
Memory(Memory&&  rhs) noexcept:
size(0),
array(nullptr)
{
  *this = std::move(rhs);
}


Memory::
Memory(const Memory&   rhs):
size(0),
array(nullptr)
{
  *this = rhs;
}


Memory::
~Memory()
{
  resize(0);
}




Memory&
Memory::
operator=(Memory&&  rhs) noexcept
{
  resize(0);

  size = rhs.size;

  std::swap(array,rhs.array);

  return *this;
}


Memory&
Memory::
operator=(const Memory&   rhs)
{
  resize(rhs.size);

  std::memcpy(array,rhs.array,rhs.size);

  return *this;
}


size_t
Memory::
get_size() const
{
  return size;
}


void
Memory::
resize(size_t  new_size)
{
    if(!new_size)
    {
      delete[] array          ;
               array = nullptr;
    }

  else
    if(new_size > size)
    {
      auto  old_array = array                        ;
                        array = new uint8_t[new_size];

      std::memcpy(array,old_array,size);

      delete[] old_array;
    }


  size = new_size;
}


uint8_t*
Memory::
get_pointer(int  ptr) const
{
  return &array[ptr];
}


int
Memory::
get8(int  ptr) const
{
  return static_cast<int8_t>(array[ptr&0xFFFFF]);
}


int
Memory::
get8u(int  ptr) const
{
  return array[ptr&0xFFFFF];
}


int
Memory::
get16(int  ptr) const
{
  return reinterpret_cast<const int16_t&>(array[ptr&0xFFFFE]);
}


int
Memory::
get16u(int  ptr) const
{
  return reinterpret_cast<const uint16_t&>(array[ptr&0xFFFFE]);
}


int
Memory::
get32(int  ptr) const
{
  return reinterpret_cast<const int32_t&>(array[ptr&0xFFFFC]);
}




void
Memory::
put8(int  ptr, int  val)
{
  array[ptr&0xFFFFF] = val;
}


void
Memory::
put16(int  ptr, int  val)
{
  reinterpret_cast<int16_t&>(array[ptr&0xFFFFE]) = val;
}


void
Memory::
put32(int  ptr, int  val)
{
  reinterpret_cast<int32_t&>(array[ptr&0xFFFFC]) = val;
}




void
Memory::
fill(int  v)
{
  std::memset(array,v,size);
}


}}




