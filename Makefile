CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L -MMD -MP
TARGET = myshell
SOURCES = src/main.c src/parser.c src/builtins.c src/executor.c src/environment.c src/redirection.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

test: $(TARGET) unit-test
	bash tests/test_cases.sh

clean:
	rm -f $(TARGET) $(OBJECTS) $(OBJECTS:.o=.d) tests/test_parser tests/test_executor

-include $(OBJECTS:.o=.d)

.PHONY: all clean test unit-test


unit-test: tests/test_parser tests/test_executor
	./tests/test_parser
	./tests/test_executor

tests/test_parser: tests/test_parser.c src/parser.c src/environment.c
	$(CC) $(CFLAGS) -Isrc -o $@ tests/test_parser.c src/parser.c src/environment.c

tests/test_executor: tests/test_executor.c src/parser.c src/executor.c src/builtins.c src/environment.c src/redirection.c
	$(CC) $(CFLAGS) -Isrc -o $@ tests/test_executor.c src/parser.c src/executor.c src/builtins.c src/environment.c src/redirection.c
