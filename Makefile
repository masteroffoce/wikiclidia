CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lncurses

SRC = main.c
EXEC = run

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)


.PHONY: all
