CC = g++
FLAGS = -std=c++11 -pedantic -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result 

FILES = TSuffixTree.cpp main.cpp
BENCH_FILES = TSuffixTree.cpp benchmark.cpp 

OUTPUT = da_lab5
BENCH_OUTPUT = benchmark

all: 
	$(CC) $(FLAGS) -o $(OUTPUT) $(FILES)
	$(CC) $(FLAGS) -o $(BENCH_OUTPUT) $(BENCH_FILES)

clean:
	rm *.o $(OUTPUT)
	rm *.o $(BENCH_OUTPUT)