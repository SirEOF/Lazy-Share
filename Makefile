DIREC = src/

all: main.o client.o server.o color.o utils.o
	gcc -o LZ main.o client.o server.o color.o utils.o

main.o:
	gcc -c src/main.c

client.o: src/client.c
	gcc -c src/client.c

server.o: src/server.c
	gcc -c src/server.c

color.o: src/color.c
	gcc -c src/color.c

utils.o: src/utils.c
	gcc -c src/utils.c

clean:
	rm -rf *.o 
