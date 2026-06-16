CC = g++
CFLAGS = -Wall -Wextra -std=c++14 -Iinclude

SRC = src/arena.cpp
EXAMPLE = examples/main.cpp
OUT = arena_example
TEST = tests/test_arena.cpp
T_OUT = arena_test

$(OUT): $(SRC) $(EXAMPLE)
	$(CC) $(CFLAGS) $(SRC) $(EXAMPLE) -o $(OUT)

run: $(OUT)
	./$(OUT)

$(T_OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(T_OUT)

test: $(T_OUT)
	./$(T_OUT)

clean:
	rm -f $(OUT)
	rm -f $(T_OUT)
