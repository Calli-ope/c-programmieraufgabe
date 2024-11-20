CC = gcc
TARGET = par

all: $(TARGET)

$(TARGET): par.o ../com/com.o
	$(CC) -o $(TARGET) par.o ../com/com.o

par.o : par.c par.h
	$(CC) -c par.c

../com/com.o :
	$(MAKE) -C ../com com.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
