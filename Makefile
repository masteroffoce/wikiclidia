CC = gcc
PKG_CONFIG = pkg-config

SRC = main.c scrape.c parse.c scrape.h parse.h
OBJ = $(SRC:.c=.o)
EXEC = run

CFLAGS = -Wall -Werror $(shell $(PKG_CONFIG) --cflags libxml-2.0)
LDFLAGS = $(shell $(PKG_CONFIG) --libs libxml-2.0) -lcurl -lcjson  -lncurses

.PHONY: all clean test
	
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(EXEC)
	@echo -------------
	@echo ''
	./$(EXEC)
	@echo ''
	@echo ''
	@echo -------------

clean:
	rm -f $(OBJ) $(EXEC)
