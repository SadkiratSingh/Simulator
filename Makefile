CC = g++
CFLAGS = -c -Wall -g -I./
LDFLAGS = -lxerces-c-3.2 -std=c++11

all: MyDOMParser

MyDOMParser: MyDOMParser.o
	$(CC) MyDOMParser.o $(LDFLAGS) -o MyDOMParser
MyDOMParser.o: MyDOMParser.cpp
	$(CC) $(CFLAGS) MyDOMParser.cpp -o MyDOMParser.o
	
clean:
	rm -f *.o MyDOMParser
