CC = gcc
CFLAGS = -Wall 
LIBS = -lpthread
OBJ = Que2.o main.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
all: Que2
Que2: Que2.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
clean: 
	rm -rf *.o Que2

