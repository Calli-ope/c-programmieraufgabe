CC = gcc
TARGET = par

all: $(TARGET)

$(TARGET): par.o ../com/com.o ../utils/rand.o
	$(CC) -o $(TARGET) par.o ../com/com.o ../utils/rand.o

par.o : par.c par.h
	$(CC) -c par.c

../com/com.o :
	$(MAKE) -C ../com com.o

../../utils/rand.o :
	$(CC) -c ../utils/rand.c -o ../utils/rand.o

run: $(TARGET)
	./$(TARGET)

clean:
	del -f *.o $(TARGET).exe