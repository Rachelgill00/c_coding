CC = gcc
OBJS = test_rbTree.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

test_rbTree.o: test_rbTree.c
	$(CC) -c -g test_rbTree.c

clean:
	rm -f *.o
	rm -f executable