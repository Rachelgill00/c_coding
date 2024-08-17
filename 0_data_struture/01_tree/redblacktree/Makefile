CC = gcc
OBJS = red_black_tree.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

red_black_tree.o: red_black_tree.c
	$(CC) -c -g red_black_tree.c

clean:
	rm -f *.o
	rm -f executable