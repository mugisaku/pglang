BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Iexpr -Ivm -Iparser  -Werror -Wno-unused-result
LDFLAGS  =

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


OBJ =                          \
  parser/pglang_parser__tag.o        \
  parser/pglang_parser__token.o       \
  parser/pglang_parser__block.o       \
  parser/pglang_parser__stream.o      \
  parser/pglang_parser__stream_character.o  \
  parser/pglang_parser__stream_number.o     \
  parser/pglang_parser__unicode.o           \
  pglang_decl.o                \
  pglang_scope.o               \
  pglang_block.o               \
  pglang_stmt.o                \
  pglang_type.o                \
  pglang_type__is.o            \
  pglang_type__struct.o        \
  pglang_type__union.o         \
  pglang_type__enum.o          \
  pglang_type__array.o         \
  pglang_type__parameter.o     \
  pglang_type__signature.o     \
  pglang_type__function.o      \
  expr/pglang_expr__element.o       \
  expr/pglang_expr__operator.o      \
  expr/pglang_expr__value.o         \
  expr/pglang_expr__value_assign.o  \
  expr/pglang_expr__value_unary.o   \
  expr/pglang_expr__value_binary.o  \
  expr/pglang_expr__literal.o       \
  expr/pglang_expr__initializer.o   \
  expr/pglang_expr.o                \
  vm/pglang_vm__memory.o          \
  vm/pglang_vm__binary.o          \
  vm/pglang_vm__instruction.o     \
  vm/pglang_vm__context.o         \


all: $(OBJ)
	$(CXX) -o test_type test_type.cpp $(OBJ) $(CXXFLAGS)
	$(CXX) -o test_parser test_parser.cpp $(OBJ) $(CXXFLAGS)


clean:
	rm -f $(OBJ) test_type test_parser log




