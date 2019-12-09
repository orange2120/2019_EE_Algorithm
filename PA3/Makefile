CC = g++
CFLAGS = -std=c++11 -Wall

OPTFLAGS = -O3
DBGFLAGS = -g

TARGET = cb
.PHONY: all clean

all: $(TARGET)

cb: src/cb.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)