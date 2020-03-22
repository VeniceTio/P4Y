CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: filtreMedian bruitImpulsionnel bruitGaussien MeanSquareError

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

filtreMedian: filtreMedian.o fileio.o
	$(CC) $(CPPFLAGS) filtreMedian.o fileio.o -o filtreMedian

filtreMedian.o: filtreMedian.cpp
	$(CC) $(CPPFLAGS) -c filtreMedian.cpp

bruitImpulsionnel: bruitImpulsionnel.o fileio.o
	$(CC) $(CPPFLAGS) bruitImpulsionnel.o fileio.o -o bruitImpulsionnel

bruitImpulsionnel.o: bruitImpulsionnel.cpp
	$(CC) $(CPPFLAGS) -c bruitImpulsionnel.cpp

bruitGaussien: bruitGaussien.o fileio.o
	$(CC) $(CPPFLAGS) bruitGaussien.o fileio.o -o bruitGaussien

bruitGaussien.o: bruitGaussien.cpp
	$(CC) $(CPPFLAGS) -c bruitGaussien.cpp

MeanSquareError: MeanSquareError.o fileio.o
	$(CC) $(CPPFLAGS) MeanSquareError.o fileio.o -o MeanSquareError

MeanSquareError.o: MeanSquareError.cpp
	$(CC) $(CPPFLAGS) -c MeanSquareError.cpp

clean:
	rm *.o