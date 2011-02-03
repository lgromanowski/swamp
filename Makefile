EXEC = swamp
CPP = g++
CXXFLAGS = -O2 -Wall -Wextra -Werror -Wformat-security
LDFLAGS = -lstdc++

SRCS = $(wildcard ./*.cpp)
OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
	

$(EXEC): $(OBJS)
	$(CPP) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $@
	

clean:
	rm ./*.o
	rm ./$(EXEC)

install:
	mkdir ./build
	cp ./$(EXEC) ./build

all: $(SRCS) $(EXEC) install
	
