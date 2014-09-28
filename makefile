CC = clang++
CFLAGS = -g -std=c++1y -pedantic
OBJECTS = build/test.o
TARGET = test


all: build run_tests
build: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

build/test.o: test.cpp flist.hpp
	mkdir -p build
	$(CC) $(CFLAGS) -o build/test.o -c test.cpp

run_tests:
	./test

clean:        
	rm -rf $(TARGET) build/