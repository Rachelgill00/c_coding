CC = clang
CFLAGS = -g
OBJS = rbtree_insert.o

executable: $(OBJS)
	$(CC) $(CFLAGS) -o executable $(OBJS)

rbtree_insert.o: rbtree_insert.c
	$(CC) $(CFLAGS) -c rbtree_insert.c

clean:
	rm -f *.o
	rm -f executable
