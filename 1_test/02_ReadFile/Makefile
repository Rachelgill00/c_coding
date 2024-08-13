CC = gcc
OBJS = readfile.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

readfile.o: readfile.c
	$(CC) -c -g readfile.c

clean:
	rm -f *.o
	rm -f executable