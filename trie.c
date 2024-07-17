/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

trie_node_t *trie_create_node(void)
{
	/**
	 * Allocates space defensively for the node
	 * and assigns each field of the stucture
	 */
	trie_node_t *node = malloc(sizeof(trie_node_t));
	DIE(!node, "Malloc for node allocation failed");

	node->end_of_word = 0;
	node->n_children = 0;
	node->count_word = 0;

	node->children = calloc(ALPHABET_SIZE, sizeof(trie_node_t *));
	DIE(!node->children, "Calloc for children allocation failed");

	return node;
}

trie_t *trie_create(void)
{
	/**
	 * Allocates space defensively for the trie
	 * and assigns each field of the stucture
	 */
	trie_t *trie = malloc(sizeof(trie_t));
	DIE(!trie, "Malloc for trie allocation failed");

	trie->size = 0;

	trie->root = trie_create_node();
	trie->nodes = 1;

	return trie;
}

void trie_insert(trie_t *trie, char *key)
{
	trie_node_t *current = trie->root;

	for (int i = 0; key[i] != '\0'; i++) { 
		int letter = key[i] - 'a';

		/**
		 * If there is no node in the trie for this
		 * letter a new one is allocated
		 */
		if (!current->children[letter]) {
			current->children[letter] = trie_create_node();
			trie->nodes++;
			current->n_children++;
		}

		current = current->children[letter];
	}

	/**
	 * The word is finalized and counted both in the trie and in its counter
	 */
	if (!current->end_of_word) {
		current->end_of_word = 1;
		trie->size++;
	}

	current->count_word++;
}

void trie_free_subtrie(trie_t *trie, trie_node_t *node)
{
	if (!node)
		return;

	/**
	 * Child by child of the node the whole subtree
	 * of the node is freed recursively
	 */
	for (int i = 0; i < ALPHABET_SIZE && node->n_children; i++) {
		if (!node->children[i])
			continue;

		trie_free_subtrie(trie, node->children[i]);
		node->n_children--;
		node->children[i] = NULL;
	}

	/**
	 * Also, the node is freed
	 */
	free(node->children);
	free(node);

	trie->nodes--;
}

void trie_remove(trie_t *trie, char *key)
{
	trie_node_t *current = trie->root;
	trie_node_t *parent = trie->root;
	int parent_letter = (key[0] - 'a');

	/**
	 * Iterates letter by letter of the word to
	 * be deleted to reach the last letter node
	 */
	for (int i = 0; key[i] != '\0'; i++) {
		int letter = key[i] - 'a';

		if (!current->children[letter])
			return;

		if (current->n_children > 1 || current->end_of_word) {
			parent = current;
			parent_letter = letter;
		}

		current = current->children[letter];
	}

	current->end_of_word = 0;
	current->count_word = 0;

	/**
	 * If the word to be deleted is not a prefix for another word
	 * is released from memory, otherwise set end_of_word to 0
	 */
	if (!current->n_children) {
		trie_free_subtrie(trie, parent->children[parent_letter]);
		parent->children[parent_letter] = NULL;
		parent->n_children--;
	}

	trie->size--;
}

void trie_free(trie_t **ptrie)
{
	/**
	 * The memory of the subtree formed by root and root is freed.
	 * This frees the memory of the entire tree
	 */
	trie_free_subtrie(*ptrie, (*ptrie)->root);
	free(*ptrie);
}

void load_file(trie_t *trie, char *filename)
{
	FILE *in = fopen(filename, "rt");
	DIE(!in, "Can't open the ascii file");

	char word[MAX_COMPLETE];
	while (!feof(in)) {
		fscanf(in, "%s", word);
		trie_insert(trie, word);
	}

	fclose(in);
}

void dfs_autocorrect(trie_node_t *node, char *word, char *correct, int diff,
					 int k, int *ok)
{
	/**
	 * If there are more than k letters different
	 * from word it exits the function
	 */
	if (diff > k) {
		return;
	}

	/**
	 * If in correct is a word with the same length as input word and if
	 * the number of different letters is less than or equal to with k
	 * and if the sequence of letters forming the word displays the word
	 */
	if (!strcmp(word, "")) {
		if (diff <= k && node->end_of_word) {
			printf("%s\n", correct);
			*ok = 1;
		}
		return;
	}

	int letter = *word - 'a';
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			/**
			 * Puts a letter in the output word
			 */
			size_t len = strlen(correct);
			correct[len] = 'a' + i;
			correct[len + 1] = '\0';

			/**
			 * Recalls the function based on the matching letters
			 */
			dfs_autocorrect(node->children[i], word + 1, correct,
							diff + (i != letter), k, ok);

			correct[strlen(correct) - 1] = '\0';
		}
	}
}

void autocorrect(trie_t *trie, char *word, int k)
{
	char *correct = malloc((strlen(word) + 1) * sizeof(char));
	DIE(!correct, "Malloc for correct word allocation failed");

	int ok = 0;
	correct[0] = '\0';
	dfs_autocorrect(trie->root, word, correct, 0, k, &ok);

	if (!ok) {
		printf("No words found\n");
	}

	free(correct);
}

void dfs_lexico(trie_node_t *node, char *complete, int *ok)
{
	/**
	 *  If the word is found, it is displayed and no further
	 *  iteration of the children is entered
	 */
	if (node->end_of_word) {
		*ok = 1;
		printf("%s\n", complete);
		return;
	}

	/**
	 * Iterating through 'a' to 'z' everytime we search for the next letter,
	 * knows for sure that the first word found is the smallest lexicographic
	 */
	for (int i = 0; i < ALPHABET_SIZE && !*ok; i++) {
		if (node->children[i]) {
			size_t len = strlen(complete);
			complete[len] = 'a' + i;
			complete[len + 1] = '\0';

			dfs_lexico(node->children[i], complete, ok);

			complete[len] = '\0';
		}
	}
}

void dfs_shortest(trie_node_t *node, char *complete, char *current,
				  char *prefix)
{
	/**
	 * Firstly, puts in complete word the first word founded,
	 * replacing the prefix and then assings the shortest one
	 * in following recursions
	 */
	if (node->end_of_word) {
		if (strlen(complete) == strlen(prefix)) {
			strcpy(complete, current);
		}

		if (strlen(current) < strlen(complete)) {
			strcpy(complete, current);
		}

		return;
	}

	/**
	 *  Creates the word adding letter by letter
	 */
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			size_t len = strlen(current);
			current[len] = 'a' + i;
			current[len + 1] = '\0';

			dfs_shortest(node->children[i], complete, current, prefix);
			current[len] = '\0';
		}
	}
}

void dfs_frequent(trie_node_t *node, char *complete, char *current, int *max)
{
	/**
	 * Compares every word's frequency with a maximum
	 * variable and assigns the word in the output variable
	 */
	if (node->end_of_word) {
		if (node->count_word > *max) {
			strcpy(complete, current);
			*max = node->count_word;
		}
	}

	/**
	 *  Creates the word adding letter by letter
	 */
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			size_t len = strlen(current);
			current[len] = 'a' + i;
			current[len + 1] = '\0';

			dfs_frequent(node->children[i], complete, current, max);
			current[len] = '\0';
		}
	}
}

void autocomplete(trie_t *trie, char *prefix, int criterion)
{
	char *current = malloc(MAX_COMPLETE * sizeof(char));
	DIE(!current, "Malloc for current word allocation failed");

	char *complete = malloc(MAX_COMPLETE * sizeof(char));
	DIE(!complete, "Malloc for lexico word allocation failed");

	strcpy(current, prefix);
	strcpy(complete, prefix);

	trie_node_t *node = trie->root;

	/**
	 * Goes through the prefix in trie (it doesn't make sense to start
	 * from the root if the word to be displayed starts with this prefix)
	 */
	for (int i = 0; prefix[i] != '\0' && node; i++) {
		int index = prefix[i] - 'a';
		node = node->children[index];
	}

	/**
	 * If the prefix doesn't exits no word can be founded
	 */
	if (!node) {
		if (!criterion) {
			printf("No words found\n");
			printf("No words found\n");
			printf("No words found\n");
		
		} else {
			printf("No words found\n");
		}
		
		free(complete);
		free(current);
		return;
	}

	int ok = 0, max = 0;

	if (criterion == 1) {
		dfs_lexico(node, complete, &ok);

	} else if (criterion == 2) {
		dfs_shortest(node, complete, current, prefix);
		printf("%s\n", complete);
	
	} else if (criterion == 3) {
		dfs_frequent(node, complete, current, &max);
		printf("%s\n", complete);

	} else {
		dfs_lexico(node, complete, &ok);

		dfs_shortest(node, complete, current, prefix);
		printf("%s\n", complete);

		dfs_frequent(node, complete, current, &max);
		printf("%s\n", complete);
	}

	free(complete);
	free(current);
}
