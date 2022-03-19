CC=g++
FLAGS=-std=c++14 -pedantic -Wall -Wextra -Wno-unused-variable
OUTPUT=da_lab1
OUTPUT_BENCHMARK=benchmark

all: sort.o da_lab1.cpp
	$(CC) $(FLAGS) sort.o da_lab1.cpp -o $(OUTPUT)
benchmark: sort.o benchmark.cpp
	$(CC) $(FLAGS) sort.o benchmark.cpp -o $(OUTPUT_BENCHMARK)
sort.o: sort.cpp sort.hpp
	$(CC) $(FLAGS) -c sort.cpp
clean:
	rm *.o $(OUTPUT)