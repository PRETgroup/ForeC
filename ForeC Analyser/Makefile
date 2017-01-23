# ForeC Analyser Makefile.

# Determine best C++ compiler to use
ifeq ($(shell uname), Linux)
	CC					= clang++
else ifeq ($(shell uname), Darwin)
	CC					= clang++
else
	CC					= g++
endif

#CFLAGS					= -O0 -Wall -g
CFLAGS					= -O3 -Wall

CFG_SOURCES				= $(wildcard cfg/*.cpp)
CFG_OBJS				= $(CFG_SOURCES:.cpp=.o)

MAXPLUS_SOURCES			= $(wildcard maxplus/*.cpp)
MAXPLUS_OBJS			= $(MAXPLUS_SOURCES:.cpp=.o)

REACHABILITY_SOURCES	= $(wildcard reachability/*.cpp)
REACHABILITY_OBJS		= $(REACHABILITY_SOURCES:.cpp=.o)

TOOLS_SOURCES			= $(wildcard tools/*.cpp)
TOOLS_OBJS				= $(TOOLS_SOURCES:.cpp=.o)

BIN						= foreca

# Binary
$(BIN) : ParserMicroBlaze.o ScannerMicroBlaze.o ParserPtarm.o ScannerPtarm.o $(CFG_OBJS) $(CFG_SOURCES:.cpp=.hpp) $(MAXPLUS_OBJS) $(MAXPLUS_SOURCES:.cpp=.hpp) $(REACHABILITY_OBJS) $(REACHABILITY_SOURCES:.cpp=.hpp) $(TOOLS_OBJS) $(TOOLS_SOURCES:.cpp=.hpp) Main.cpp File.hpp
	$(CC) $(CFLAGS) Main.cpp $(CFG_OBJS) $(MAXPLUS_OBJS) $(REACHABILITY_OBJS) $(TOOLS_OBJS) ScannerMicroBlaze.o ParserMicroBlaze.o ParserPtarm.o ScannerPtarm.o -o $(BIN)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
# Parser (MicroBlaze, Ptarm)
ParserMicroBlaze.o : ParserMicroBlaze.y
	bison ParserMicroBlaze.y
	$(CC) $(CFLAGS) -x c++ -c -o ParserMicroBlaze.o ParserMicroBlaze.tab.c 

ParserPtarm.o : ParserPtarm.y
	bison ParserPtarm.y
	$(CC) $(CFLAGS) -x c++ -c -o ParserPtarm.o ParserPtarm.tab.c 

# Scanner (MicroBlaze, Ptarm)
ScannerMicroBlaze.o : ParserMicroBlaze.y ScannerMicroBlaze.l ScannerMicroBlaze.hpp
	flex ScannerMicroBlaze.l
	$(CC) $(CFLAGS) -c -o ScannerMicroBlaze.o lex.microBlaze.cc

ScannerPtarm.o : ParserPtarm.y ScannerPtarm.l ScannerPtarm.hpp
	flex ScannerPtarm.l
	$(CC) $(CFLAGS) -c -o ScannerPtarm.o lex.ptarm.cc
	
clean :
	# remove bison generated files
	rm -rf ParserMicroBlaze.tab.c ParserMicroBlaze.tab.h ParserPtarm.tab.c ParserPtarm.tab.h location.hh position.hh stack.hh
	
	# remove flex generated files
	rm -rf lex.microBlaze.cc lex.ptarm.cc
	
	# remove compiled files
	rm -rf $(BIN) $(BIN).exe *.o $(MAXPLUS_OBJS) $(REACHABILITY_OBJS) $(CFG_OBJS) $(TOOLS_OBJS)

