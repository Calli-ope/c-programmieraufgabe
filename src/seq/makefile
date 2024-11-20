CC = gcc
TARGET = seq

all: $(TARGET)

$(TARGET): seq.o ../com/com.o ../utils/rand.o
	$(CC) -o $(TARGET) seq.o ../com/com.o ../utils/rand.o

seq.o : seq.c seq.h
	$(CC) -c seq.c

../com/com.o :
	$(MAKE) -C ../com com.o

../../utils/rand.o :
	$(CC) -c ../utils/rand.c -o ../utils/rand.o

run: $(TARGET)
	./$(TARGET)

clean:
	del -f *.o $(TARGET).exe