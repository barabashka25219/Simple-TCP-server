CC=gcc

install: main.o tcp_server.o
	$(CC) main.o tcp_server.o -o tcp_server
	rm -rf *.o

main.o:
	gcc -c main.c

tcp_server.o:
	gcc -c server/tcp_server.c 
