CC = clang
CFLAGS = -g
OBJS = rb_tree.o

executable: $(OBJS)
	$(CC) $(CFLAGS) -o executable $(OBJS)

rb_tree.o: rb_tree.c
	$(CC) $(CFLAGS) -c rb_tree.c

clean:
	rm -f *.o
	rm -f executable
