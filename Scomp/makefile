prog := bin/SimpleComputer
CC := gcc
CFLAGS := -Wall -std=c99

.PHONY: all clean dir

all: $(prog)

$(prog): build/main.o build/SimpleComputer.o build/myTerm.o build/myBigChars.o build/myReadkey.o build/myHandler.o build/CU.o build/ALU.o build/PrintElements.o
	$(CC) $(CFLAGS) build/main.o build/SimpleComputer.o build/myTerm.o build/myBigChars.o build/myReadkey.o build/myHandler.o build/CU.o build/ALU.o build/PrintElements.o -o $(prog) -lm
build/main.o: src/main.c src/SimpleComputer.h 
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
build/SimpleComputer.o: src/SimpleComputer.c src/SimpleComputer.h 
	$(CC) $(CFLAGS) -c src/SimpleComputer.c -o build/SimpleComputer.o -lm
build/myTerm.o: src/myTerm.c src/SimpleComputer.h src/myTerm.h
	$(CC) $(CFLAGS) -c src/myTerm.c -o build/myTerm.o 
build/myBigChars.o: src/myBigChars.c src/myTerm.h src/myBigChars.h 
	$(CC) $(CFLAGS) -c src/myBigChars.c -o build/myBigChars.o -lm
build/myReadkey.o: src/myReadkey.c src/myReadkey.h
	$(CC) $(CFLAGS) -c src/myReadkey.c -o build/myReadkey.o
build/myHandler.o: src/myHandler.c src/myHandler.h
	$(CC) $(CFLAGS) -c src/myHandler.c -o build/myHandler.o
build/CU.o: src/CU.c src/CU.h
	$(CC) $(CFLAGS) -c src/CU.c -o build/CU.o
build/ALU.o: src/ALU.c src/ALU.h
	$(CC) $(CFLAGS) -c src/ALU.c -o build/ALU.o
build/PrintElements.o: src/PrintElements.c src/PrintElements.h
	$(CC) $(CFLAGS) -c src/PrintElements.c -o build/PrintElements.o

clean:
	@rm -rf build/*.o

dir:
	@mkdir build
	@mkdir bin
