CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main convolve

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

convolve: convolve.o fileio.o
	$(CC) $(CPPFLAGS) convolve.o fileio.o -o convolve

convolve.o: convolve.cpp
	$(CC) $(CPPFLAGS) -c convolve.cpp

clean:
	rm *.o