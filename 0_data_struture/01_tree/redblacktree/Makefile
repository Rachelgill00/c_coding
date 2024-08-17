CC = gcc
OBJS = rb_tree.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

rb_tree.o: rb_tree.c
	$(CC) -c -g rb_tree.c

clean:
	rm -f *.o
	rm -f executable