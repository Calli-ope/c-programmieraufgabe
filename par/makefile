CC = gcc
TARGET = par

all: $(TARGET)

$(TARGET): par.o ../com/progs.o
	$(CC) -o $(TARGET) par.o ../com/progs.o

par.o: par.c par.h ../com/com.h
	$(CC) -c par.c

run: $(TARGET)
	./$(TARGET)

clean:
	del -f *.o $(TARGET).exe