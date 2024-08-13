CC = gcc
OBJS = binary_tree.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

binary_tree.o: binary_tree.c
	$(CC) -c -g binary_tree.c

clean:
	rm -f *.o
	rm -f executable