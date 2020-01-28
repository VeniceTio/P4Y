CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main compute_histo degrade equalize negate normalize

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

degrade: degrade.o fileio.o
	$(CC) $(CPPFLAGS) degrade.o fileio.o -o degrade

degrade.o: degrade.cpp 
	$(CC) $(CPPFLAGS) -c degrade.cpp

equalize: equalize.o fileio.o
	$(CC) $(CPPFLAGS) equalize.o fileio.o -o equalize

equalize.o: equalize.cpp 
	$(CC) $(CPPFLAGS) -c equalize.cpp

negate: negate.o fileio.o
	$(CC) $(CPPFLAGS) negate.o fileio.o -o negate

negate.o: negate.cpp 
	$(CC) $(CPPFLAGS) -c negate.cpp

normalize: normalize.o fileio.o
	$(CC) $(CPPFLAGS) normalize.o fileio.o -o normalize

normalize.o: normalize.cpp 
	$(CC) $(CPPFLAGS) -c normalize.cpp

clean:
	rm *.o