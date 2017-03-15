CC=g++
CFLAGS=-c -Wall -std=c++11 -g
LDFLAGS=
SOURCES=main.cpp Smart_string.cpp file_reader.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
tonbk2:
	rsync -rv ./ vitaly@nbk2:WS/SmartString
fromnbk2:
	rsync -rv vitaly@nbk2:WS/SmartString ../
tst:
	valgrind ./$(EXECUTABLE) data.txt
run:
	./$(EXECUTABLE) data.txt param1 param2 "param 3 3 3 3 3"
