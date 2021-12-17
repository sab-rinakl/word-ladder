CXX = g++
CPPFLAGS = -Wall -g

all: wordladder

clean:
	rm *.o

wordladder: wordladder.cpp MinHeap.h
	$(CXX) $(CPPFLAGS) wordladder.cpp MinHeap.h -o wordladder