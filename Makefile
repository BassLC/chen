CC=clang++ -std=c++14 -Wall -Werror -Wpedantic
OBJS=$(wildcard src/*.cpp)

debug: $(OBJS)
	$(CC) $(OBJS) -g -o debug

chen: $(OBJS)
	$(CC) $(OBJS) -O3 -o chen

test: $(OBJS) $(wildcard tests/*)
	$(CC) $(shell find src/ -type f ! -name "main.cpp") tests/main.cpp -o test

.PHONY: clean
clean:
	rm debug chen test
