CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main compute_histo normalize equalize

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp
histogram.o: histogram.cpp 
	$(CC) $(CPPFLAGS) -c histogram.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main
compute_histo: compute_histo.o fileio.o histogram.o
	$(CC) $(CPPFLAGS) compute_histo.o fileio.o histogram.o -o compute_histo
normalize: normalize.o fileio.o histogram.o
	$(CC) $(CPPFLAGS) normalize.o fileio.o histogram.o -o normalize
equalize: equalize.o fileio.o histogram.o
	$(CC) $(CPPFLAGS) equalize.o fileio.o histogram.o -o equalize

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp
compute_histo.o: compute_histo.cpp 
	$(CC) $(CPPFLAGS) -c compute_histo.cpp
normalize.o: normalize.cpp 
	$(CC) $(CPPFLAGS) -c normalize.cpp
equalize.o: equalize.cpp 
	$(CC) $(CPPFLAGS) -c equalize.cpp

clean:
	rm *.o