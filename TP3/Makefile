CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main bord

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

bord: extract_border.o fileio.o
	$(CC) $(CPPFLAGS) extract_border.o fileio.o -o bord

extract_border.o: extract_border.cpp
	$(CC) $(CPPFLAGS) -c extract_border.cpp

clean:
	rm *.o