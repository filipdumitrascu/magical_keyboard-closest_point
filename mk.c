/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

int main(void)
{
	int exit = 0, k, criterion;
	char *command, *word, *filename, *prefix;
	trie_t *trie = trie_create();

	/**
	 *  As long as the exit string has not been received as input,
	 *  call the specific function to each command.
	 *
	 *  To not define a guessed constant representing the maximum
	 *  number of letters a command/word can have, reads with %ms
	 *  to dynamically allocate them until space.
	 */
	while (!exit) {
		scanf("%ms", &command);
		if (!strcmp(command, "INSERT")) {
			scanf("%ms", &word);
			trie_insert(trie, word);
			free(word);

		} else if (!strcmp(command, "LOAD")) {
			scanf("%ms", &filename);
			load_file(trie, filename);
			free(filename);

		} else if (!strcmp(command, "REMOVE")) {
			scanf("%ms", &word);
			trie_remove(trie, word);
			free(word);

		} else if (!strcmp(command, "AUTOCORRECT")) {
			scanf("%ms %d", &word, &k);
			autocorrect(trie, word, k);
			free(word);

		} else if (!strcmp(command, "AUTOCOMPLETE")) {
			scanf("%ms %d", &prefix, &criterion);
			autocomplete(trie, prefix, criterion);
			free(prefix);

		} else {
			trie_free(&trie);
			exit = 1;
		}

		free(command);
	}

	return 0;
}
