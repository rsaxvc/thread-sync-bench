CXX=g++
CXXFLAGS= -O3 -g -Wall
CC=$(CXX)
LDFLAGS=-lpthread -lrt
BUILDS=bench
NUM_POINTS=1000000
SOURCE=*.cpp

all:$(BUILDS)

bench: $(SOURCE)
	g++ $(SOURCE) -o bench $(LDFLAGS) $(CXXFLAGS)

benchmarks: $(BENCHMARK_FILES)

main.o: main.cpp

clean:
	rm -f *.o $(BUILDS)

