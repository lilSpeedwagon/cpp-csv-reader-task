CC=g++
INCLUDES=-I./thirdparty/ -I./
CFLAGS=-c -Wall $(INCLUDES)

SOURCES=main.cpp csv_reader.cpp
TESTS=./tests/csv_reader_test.cpp csv_reader.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TESTS_OBJECTS=$(subst tests/,,$(TESTS:.cpp=.o))

EXECUTABLE=cpp-csv-reader
TEST_EXECUTABLE=cpp-csv-reader-test


all: build

build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

compile: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

test: build-test
	./$(TEST_EXECUTABLE)

build-test: compile-test
	$(CC) $(TESTS_OBJECTS) -o $(TEST_EXECUTABLE)

compile-test: $(TESTS)
	$(CC) $(CFLAGS) $(TESTS)

clean:
	rm -rf *.o $(EXECUTABLE) $(TEST_EXECUTABLE)