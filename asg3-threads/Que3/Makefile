CC = gcc
CFLAGS = -Wall 
LIBS = -lpthread -lm
OBJ = Que3.o main.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
all: Que3
Que3: Que3.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
clean: 
	rm -rf *.o Que3

