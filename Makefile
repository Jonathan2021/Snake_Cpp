CXX = g++
LDFLAGS = -lncurses
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++17
SRC = $(wildcard src/*.cc)
OBJ = $(SRC:.cc=.o)
TESTOBJ = snaketest.o $(filter-out src/game.o, $(OBJ))
BIN = snake

.PHONY: clean all check run

all: $(BIN)

%.o: src/%.cc
	$(CXX) -c -o $@ $< $(CFLAGS) $(CXXFLAGS) $(LDFLAGS)
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(@) $^ $(LDFLAGS)

test: $(TESTOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

check: $(BIN) test
	cd tests && ./runtests

run: $(BIN)
	./$(BIN)

clean:
	$(RM) $(BIN)
	$(RM) $(OBJ) $(TESTOBJ)
