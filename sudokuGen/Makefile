CC=g++
CFLAGS= -c -Wall -g
LDFLAGS=
SOURCES= Sudocu.cpp sudoku_generator.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sudoku.out

sudoku: clear $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

clear:
	rm -rf $(OBJECTS) $(EXECUTABLE)

$(OBJECTS) :
	$(CC) $(CFLAGS) $(SOURCES) 

	