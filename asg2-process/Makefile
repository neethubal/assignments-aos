CC = gcc
CFLAGS = -Wall
OBJ = Que1.o Que2.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
all: Que1 Que2
Que1: Que1.o
	$(CC) $(CFLAGS) -o $@ $^	
Que2: Que2.o
	$(CC) $(CFLAGS) -o $@ $^
clean: 
	rm -rf *.o Que1 Que2
