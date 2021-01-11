CC = gcc
AR = ar
FLAGS = -Wall -g
OBJ = frequency

.PHONY: clean all

all: frequency

#frequency: frequency.o
#	$(CC) $(FLAGS) -o frequency $(OBJ)

frequency: main.c
	$(CC) $(FLAGS) -c main.c -o frequency

clean:
	rm -f *.o *.a *.so frequency