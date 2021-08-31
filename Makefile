CC=g++
INCLUDES=-I./thirdparty/ -I./
CFLAGS=-c -Wall $(INCLUDES)

MAIN=main.cpp
SOURCES=csv_reader.cpp
TESTS=./tests/csv_reader_test.cpp
MAIN_OBJ=main.o
OBJECTS=$(SOURCES:.cpp=.o)
TESTS_OBJECTS=$(subst tests/,,$(TESTS:.cpp=.o))

EXECUTABLE=cpp-csv-reader.out
TEST_EXECUTABLE=cpp-csv-reader-test.out


all: build

build: $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(OBJECTS) $(MAIN_OBJ) -o $(EXECUTABLE)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) $(MAIN)

test: build-test
	./$(TEST_EXECUTABLE)

build-test: $(TESTS_OBJECTS) $(OBJECTS)
	$(CC) $(TESTS_OBJECTS) $(OBJECTS) -o $(TEST_EXECUTABLE)

$(TESTS_OBJECTS): $(TESTS)
	$(CC) $(CFLAGS) $(TESTS)

clean:
	rm -rf *.o $(EXECUTABLE) $(TEST_EXECUTABLE)