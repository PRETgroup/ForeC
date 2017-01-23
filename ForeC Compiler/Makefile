# ForeC Compiler Makefile.

# Determine best C++ compiler to use
ifeq ($(shell uname), Linux)
	CC			= clang++
else ifeq ($(shell uname), Darwin)
	CC			= clang++
else
	CC			= g++
endif

CFLAGS			= -O0 -Wall -g
#CFLAGS			= -O3 -Wall

AST_SOURCES		= $(wildcard ast/*.cpp)
AST_OBJS		= $(AST_SOURCES:.cpp=.o)

TAROT_SOURCES	= $(wildcard tarot/*.cpp)
TAROT_OBJS		= $(TAROT_SOURCES:.cpp=.o)

TOOLS_SOURCES	= $(wildcard tools/*.cpp)
TOOLS_OBJS		= $(TOOLS_SOURCES:.cpp=.o)

BIN				= forecc

# Binary
$(BIN) : parser.o scanner.o $(AST_OBJS) $(AST_SOURCES:.cpp=.hpp) $(TAROT_OBJS) $(TAROT_SOURCES:.cpp=.hpp) $(TOOLS_OBJS) $(TOOLS_SOURCES:.cpp=.hpp) Main.cpp File.hpp
	$(CC) $(CFLAGS) Main.cpp $(AST_OBJS) $(TAROT_OBJS) $(TOOLS_OBJS) scanner.o parser.o -o $(BIN)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
# Parser
parser.o : parser.y
	bison parser.y
	$(CC) $(CFLAGS) -x c++ -c -o parser.o parser.tab.c 

# Scanner
scanner.o : parser.y scanner.l Scanner.hpp
	flex scanner.l
	$(CC) $(CFLAGS) -c -o scanner.o lex.yy.cc

	
clean :
	# remove bison generated files
	rm -rf parser.tab.c parser.tab.h location.hh position.hh stack.hh
	
	# remove flex generated files
	rm -rf lex.yy.cc
	
	# remove compiled files
	rm -rf $(BIN) $(BIN).exe *.o $(AST_OBJS) $(TAROT_OBJS) $(TOOLS_OBJS)

