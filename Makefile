CC = g++
CFLAGS = -c -Wall -g -I./
LDFLAGS = -lxerces-c-3.2 -std=c++11

all: XMLDOMParser

XMLDOMParser: main.o config.o
	$(CC) main.o config.o $(LDFLAGS) -o XMLDOMParser
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o
config.o: config.cpp
	$(CC) $(CFLAGS) config.cpp -o config.o
	
clean:
	rm -f *.o XMLDOMParser