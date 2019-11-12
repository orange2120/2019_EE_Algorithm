CC = g++
CFLAGS = -std=c++11 -Wall

DBGFLAGS = -g
OPTFLAGS = -O3

TARGET= maxPlanarSubset.o mps

all: $(TARGET)

mps: src/mps.cpp src/maxPlanarSubset.o
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)

maxPlanarSubset.o: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $< -o src/$@

clean:
	rm -f $(TARGET) src/*.o