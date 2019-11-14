CC = g++
CFLAGS = -std=c++11 -Wall

DBGFLAGS = -g
OPTFLAGS = -O3

TARGET= maxPlanarSubset.o mps
DBG_TARGET = maxPlanarSubsetdbg.o mps.debug

all: $(TARGET)
mps: src/mps.cpp src/maxPlanarSubset.o
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)

maxPlanarSubset.o: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $< -o src/$@

debug: $(DBG_TARGET)

mps.debug: src/mps.cpp src/maxPlanarSubsetdbg.o
	$(CC) -o $@ $^ $(CFLAGS) $(DBGFLAGS)

maxPlanarSubsetdbg.o: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
	$(CC) -c $(CFLAGS) $(DBGFLAGS) $< -o src/$@

clean:
	rm -f $(TARGET) $(DBG_TARGET) src/*.o