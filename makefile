CC = clang
CFLAGS = -O -Wall -Wextra -lpthread -std=c99 -w
LFLAGS =
LIBS = -lm
SOURCES = main.c utility.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = a.out
.PHONY: clean help

default:
	$(CC) $(CFLAGS) $(SOURCES) $< $(LIBS) -o $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"
