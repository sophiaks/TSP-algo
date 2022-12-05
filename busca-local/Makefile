CPP = g++
CUDA = nvcc
CFLAGS = -Wall -std=c++11 
CFLAGS_PAR = -g -Wall -std=c++11 -fopenmp


all: main main_parallel

main: main.cpp
	$(CPP) $(CFLAGS) main.cpp -o main

main_parallel: main_parallel.cpp
	$(CPP) $(CFLAGS_PAR) main_parallel.cpp -o main_p

main_cuda: main_cuda.cpp
	$(CPP) $(CFLAGS_PAR) main_cuda.cpp -o main_cuda

clean:
	rm *.o output