MONKEY=@

ECHO = $(MONKEY)echo
RM = $(MONKEY)rm -Rf
MKDIR = $(MONKEY)mkdir
CP = $(MONKEY)cp

CPP = $(MONKEY)g++
EXEC = swamp

CXXINCLUDES = -I. -I./character -I./database -I./item -I./server -I./world
CXXWARNINGS = -Wall -Wextra -Werror -Wformat-security
CXXFLAGS = -O2 -g $(CXXWARNINGS) $(CXXINCLUDES) 
LDFLAGS = -lstdc++

DOXYGEN = $(MONKEY)doxygen

SRCS = $(wildcard ./*.cpp)
OBJS = $(SRCS:.cpp=.o)


.cpp.o:
	$(ECHO) Compiling: $< ...
	$(CPP) $(CXXFLAGS) -c $< -o $@
	

$(EXEC): $(OBJS)
	$(ECHO) Compiling executable: $(EXEC) ...
	$(CPP) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@
	

clean:
	$(RM) ./*.o
	$(RM) ./$(EXEC)
	$(RM) ./build/*
	$(RM) ./doc/*

install:
	$(ECHO) Installing $(EXEC) ...
	$(CP) ./$(EXEC) ./build

docs:
	$(DOXYGEN) swamp.Doxyfile

all: $(SRCS) $(EXEC) docs install
	
