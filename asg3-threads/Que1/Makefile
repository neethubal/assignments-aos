CC = gcc
CFLAGS = -Wall 
LIBS = -lpthread
OBJ = Que1.o main.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
all: Que1
Que1: Que1.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
clean: 
	rm -rf *.o Que1

