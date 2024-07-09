
# This makefile is used to compile the files in the current directory.
# The makefile will compile the files and create an executable file called Demo.
# The makefile will compile the files with the following flags:



CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-value

Sources = main.cpp tree.hpp node.hpp Complex.cpp TreeGUI.hpp test.cpp

all: demo test

demo: $(Sources)
	$(CXX) $(CXXFLAGS) -g -o $@ main.cpp Complex.cpp -lSDL2 -lSDL2_ttf

test: $(Sources)
	$(CXX) $(CXXFLAGS) -g -o $@ test.cpp Complex.cpp -lSDL2 -lSDL2_ttf
clean:
	rm -f demo test *.o

.PHONY: clean