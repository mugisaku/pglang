BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I/usr/include/SDL2  -Werror -Wno-unused-result
LDFLAGS  = -lz -lpng -lSDL2_image -lSDL2 -lSDL2main

ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS += $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS += $(COMMON_LDFLAGS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -I/usr/include/SDL2 -Werror -Wno-unused-result -O2 -s USE_SDL=2 -s USE_ZLIB=1
  EXE_EXT  = .html
  LDFLAGS  = --embed-file data.bin
else ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


OBJ =                       \
  pglang_type.o             \
  pglang_type__struct.o     \
  pglang_type__union.o      \
  pglang_type__enum.o       \
  pglang_type__signature.o  \
  pglang_type__function.o   \
  pglang_type__literal.o    \
  pglang_type__book.o       \
  pglang_vm__memory.o       \
  pglang_vm__binary.o       \
  pglang_vm__instruction.o  \
  pglang_vm__context.o      \


all: $(OBJ)
	g++ -o test_type test_type.cpp $(OBJ) -std=c++11


clean:
	rm -f $(OBJ) test_type




