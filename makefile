
# This makefile is used to compile the files in the current directory.
# The makefile will compile the files and create an executable file called Demo.
# The makefile will compile the files with the following flags:



CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-value
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
SOURCES = test.cpp # main.cpp tree.hpp node.hpp TreeGUI.hpp 

DemoSources = main.cpp tree.hpp node.hpp Complex.cpp TreeGUI.hpp
testSources = test.cpp tree.hpp node.hpp Complex.cpp TreeGUI.hpp

all: demo test

demo: $(DemoSources)
	$(CXX) $(CXXFLAGS) -g -o $@ main.cpp Complex.cpp -lSDL2 -lSDL2_ttf

test: $(testSources)
	$(CXX) $(CXXFLAGS) -g -o $@ test.cpp Complex.cpp -lSDL2 -lSDL2_ttf

tidy: 
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* -- -I/usr/include/SDL2 -lSDL2 -lSDL2_ttf

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
	
clean:
	rm -f demo test *.o

.PHONY: clean