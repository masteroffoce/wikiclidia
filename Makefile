CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lcurl -lcjson -lxml2 #-lncurses

SRC = scrape.c
EXEC = run

#all: $(EXEC)
.PHONY: all
all:

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

.PHONY: test

test: $(EXEC)
	./$(EXEC)
