# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -std=c99 -O0

# define targets
TARGETS=kNN mk

build:
	$(CC) $(CFLAGS) trie.c mk.c -o mk
	$(CC) $(CFLAGS) bst.c kNN.c -o kNN -lm

pack:
	zip -FSr 312CA_DumitrascuFilipTeodor_Tema3.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
