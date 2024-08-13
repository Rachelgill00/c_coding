CC = gcc
OBJS = bubble.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

bubble.o: bubble.c
	$(CC) -c -g bubble.c

clean:
	rm -f *.o
	rm -f executable