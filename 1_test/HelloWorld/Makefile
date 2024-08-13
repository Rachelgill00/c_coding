CC = gcc
OBJS = helloworld.o

executable: $(OBJS)
	$(CC) -o executable $(OBJS)

helloworld.o: helloworld.c
	$(CC) -c -g helloworld.c

clean:
	rm -f *.o
	rm -f executable