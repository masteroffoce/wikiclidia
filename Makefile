CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lncurses

SRC = main.c
EXEC = run

#all: $(EXEC)
.PHONY: all
all:

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

.PHONY: test

test: $(EXEC)
	./$(EXEC)
