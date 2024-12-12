CC = gcc
TARGET = seq

all: $(TARGET)

$(TARGET): seq.o ../com/progs.o
	$(CC) -o $(TARGET) seq.o ../com/progs.o

seq.o: seq.c seq.h ../com/com.h
	$(CC) -c seq.c

run: $(TARGET)
	./$(TARGET)

clean:
	del -f *.o $(TARGET).exe