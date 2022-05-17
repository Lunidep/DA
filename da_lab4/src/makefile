CC=g++
FLAGS=-std=c++17 -pedantic -Wall -Wextra -Wno-unused-variable
OUTPUT=da_lab4
BENCH_OUTPUT=benchmark

all: da_lab4.cpp benchmark.cpp
	$(CC) $(FLAGS) da_lab4.cpp -o $(OUTPUT)
	$(CC) $(FLAGS) benchmark.cpp -o $(BENCH_OUTPUT)

clean:
	rm *.o $(OUTPUT)