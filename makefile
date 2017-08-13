all: 
	gcc *.c -lpthread -o main

clean:
	rm -f *.o
