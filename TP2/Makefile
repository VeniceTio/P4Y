CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main compute_histo otsu

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

compute_histo: compute_histo.o fileio.o
	$(CC) $(CPPFLAGS) compute_histo.o fileio.o -o compute_histo

compute_histo.o: compute_histo.cpp 
	$(CC) $(CPPFLAGS) -c compute_histo.cpp

otsu: otsu.o fileio.o
	$(CC) $(CPPFLAGS) otsu.o fileio.o -o otsu

otsu.o: otsu.cpp
	$(CC) $(CPPFLAGS) -c otsu.cpp

clean:
	rm *.o