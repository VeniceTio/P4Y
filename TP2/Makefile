CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main otsu

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

otsu: otsu.o fileio.o
	$(CC) $(CPPFLAGS) otsu.o fileio.o -o otsu

otsu.o: otsu.cpp
	$(CC) $(CPPFLAGS) -c otsu.cpp

clean:
	rm *.o