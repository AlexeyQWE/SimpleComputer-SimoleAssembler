prog := bin/sat
CC := gcc
CFLAGS := -Wall -std=c99

.PHONY: all clean dir

all: $(prog)

$(prog): build/main.o build/sat.o
	$(CC) $(CFLAGS) build/main.o build/sat.o -o $(prog)
build/main.o: src/main.c src/sat.h
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
build/sat.o: src/sat.c src/sat.h 
	$(CC) $(CFLAGS) -c src/sat.c -o build/sat.o

clean:
	@rm -rf build/*.o

dir:
	@mkdir build
	@mkdir bin