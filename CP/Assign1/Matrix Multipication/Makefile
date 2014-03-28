CC = icpc
CXXFLAGS = -g
SRC=./src
BIN=./bin

all: matrix

matrix:	$(SRC)/matrix-sq-re.cpp $(SRC)/matrix-sq-it.cpp $(SRC)/matrix-sq-tra.cpp
	$(CC) $(CXXFLAGS)  $(SRC)/matrix-sq-it.cpp -o  $(BIN)/matrix-sq-it
	$(CC) $(CXXFLAGS)  $(SRC)/matrix-sq-re.cpp -o  $(BIN)/matrix-sq-re
	$(CC) $(CXXFLAGS)  $(SRC)/matrix-sq-tra.cpp -o  $(BIN)/matrix-sq-tra

clean:
	rm -f  $(BIN)/matrix-sq-re  $(BIN)/matrix-sq-it $(BIN)/matrix-sq-tra

