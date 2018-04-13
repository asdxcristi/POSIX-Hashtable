#Tema1 SO,Bucur Ionut-Cristian,333CA
CC=gcc
CCFLAGS=-lhash -L.
WARNINGFLAGS=-Wall -Wextra -ansi -pedantic
BINNAME=tema1

all: build

build: $(BINNAME)

$(BINNAME): $(BINNAME).o hashtable.o utils.o commands.o
	$(CC) -o $(BINNAME) $(BINNAME).o hashtable.o utils.o commands.o $(WARNINGFLAGS) $(CCFLAGS)

$(BINNAME).o: $(BINNAME).c
	$(CC) -c $(BINNAME).c $(WARNINGFLAGS)

commands.o: commands.c
	$(CC) -c commands.c $(WARNINGFLAGS)

hashtable.o: hashtable.c
	$(CC) -c hashtable.c $(WARNINGFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(WARNINGFLAGS)

clean:
	rm -f *.o *~
	rm -f $(BINNAME) 
