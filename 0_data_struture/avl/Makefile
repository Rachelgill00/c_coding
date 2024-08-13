CC = gcc
OBJS = avl.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

avl.o: avl.c
	$(CC) -c -g avl.c

clean:
	rm -f *.o
	rm -f executable