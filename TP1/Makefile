CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o