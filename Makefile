COMPILER_CXX = g++
COMPILER_C = gcc

# File query
SOURCES = $(wildcard xor/*.cc)
HEADERS = $(wildcard xor/*.h)

# Compiler flags

# Tasks
all:
	make clean
	mkdir build
	$(COMPILER_CXX) $(SOURCES) -o build/xor -g

compile-debug:
	make clean
	mkdir build
	$(COMPILER_CXX) $(SOURCES) -o build/xor -g

compile-release:
	make clean
	mkdir build
	$(COMPILER_CXX) $(SOURCES) -o build/xor -O3

clean:
	rm -rf build
