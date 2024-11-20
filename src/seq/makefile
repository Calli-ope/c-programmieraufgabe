CC = gcc
TARGET = seq

all: $(TARGET)

$(TARGET): seq.o ../com/com.o
	$(CC) -o $(TARGET) seq.o ../com/com.o

seq.o : seq.c seq.h
	$(CC) -c seq.c

../com/com.o :
	$(MAKE) -C ../com com.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
