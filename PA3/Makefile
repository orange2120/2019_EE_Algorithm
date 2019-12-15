CC = g++
CFLAGS = -std=c++11 -Wall

# OPTFLAGS = -O3
OPTFLAGS = -g
# DBGFLAGS = -g

TARGET = CycleBreaking.o cb
.PHONY: all clean

all: $(TARGET)

cb: src/cb.cpp src/CycleBreaking.o
	$(CC) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $^ -o $@
	@echo "done."

CycleBreaking.o: src/CycleBreaking.cpp src/CycleBreaking.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o src/$@

clean:
	rm -f $(TARGET) src/*.o