all: client server

client: client.o networking.o
	gcc -o client.exe client.o networking.o
	
server: server.o networking.o
	gcc -o server.exe server.o networking.o

client.o: client.c networking.h
	gcc -c client.c

server.o: server.c networking.h
	gcc -c server.c

networking.o: networking.c networking.h
	gcc -c networking.c

client.o: client.c 
clean:
	rm -f *.o
	rm -f main