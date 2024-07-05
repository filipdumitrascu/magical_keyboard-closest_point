/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#ifndef TRIE_H
#define TRIE_H

#include "utils.h"

#define ALPHABET_SIZE 26
#define MAX_COMPLETE 50  // predicted maximum length of a completed word

typedef struct trie_node_t trie_node_t;
struct trie_node_t {
	int end_of_word; // 1 if the subscript so far makes a word, 0 otherwise
	int n_children;  // number of children of the node
	int count_word;  // if end_of_word, the number of appearances increases
	trie_node_t **children; // 26 letters array
};

typedef struct trie_t trie_t;
struct trie_t {
	trie_node_t *root;
	int size; // number of words in the trie
	int nodes; // number of nodes in the trie
};

/**
 * @brief The function returns a dynamically allocated
 * node structure with all fields initialized
 * 
 * @return trie_node_t* 
 */
trie_node_t *trie_create_node(void);

/**
 * @brief The function returns a dynamically allocated
 * trie structure with all fields initialized
 * 
 * @return trie_t* 
 */
trie_t *trie_create(void);

/**
 * @brief The function inserts a new word in the trie
 * 
 * @param trie the trie
 * @param key the key
 */
void trie_insert(trie_t *trie, char *key);

/**
 * @brief The function is called recursively from a node and frees
 * the memory of the entire subtree formed by this node
 * 
 * @param trie the trie
 * @param node the node
 */
void trie_free_subtrie(trie_t *trie, trie_node_t *node);

/**
 * @brief The function deletes a word from the string. If the
 * word is a prefix of another word, only the end_of_word counter
 * for the word to be deleted is modified.
 * 
 * @param trie the trie
 * @param key the key
 */
void trie_remove(trie_t *trie, char *key);

/**
 * @brief The function frees the memory of the trie
 * 
 * @param ptrie the pointer of the trie
 */
void trie_free(trie_t **ptrie);

/**
 * @brief The function reads word by word from the file
 * and inserts it into the tree
 * 
 * @param trie the trie
 * @param filename the file name
 */
void load_file(trie_t *trie, char *filename);

/**
 * @brief The function iterates (dfs) through the trie and displays
 * which words differ by k letters from the one received as input
 * 
 * @param node the node 
 * @param word the word
 * @param correct the correct 
 * @param diff teh difference
 * @param k count
 * @param ok sort fo boolean
 */
void dfs_autocorrect(trie_node_t *node, char *word, char *correct, int diff,
					 int k, int *ok);

/**
 * @brief The function autocorrects a word using the dfs
 * 
 * @param trie teh trie
 * @param word teh word
 * @param k count
 */
void autocorrect(trie_t *trie, char *word, int k);

/**
 * @brief Iterates through the trie using dfs and displays
 * the smallest lexicographic word with the given prefix
 * 
 * @param node the node
 * @param complete the complete
 * @param ok boolean
 */
void dfs_lexico(trie_node_t *node, char *complete, int *ok);

/**
 * @brief Iterates through the trie using dfs and displays
 * the shortest word with the given prefix
 * 
 * @param node the node
 * @param complete the complete
 * @param current current word
 * @param prefix the prefix
 */
void dfs_shortest(trie_node_t *node, char *complete, char *current,
				  char *prefix);

/**
 * @brief Iterates through the trie using dfs and displays
 * the most frequent word with the given prefix
 * 
 * @param node the node
 * @param complete the complete
 * @param current current node
 * @param max maximum
 */
void dfs_frequent(trie_node_t *node, char *complete, char *current, int *max); 

/**
 * @brief The function autocompletes the word using the dfs function
 * 
 * @param trie the trie
 * @param prefix the prefix
 * @param criterion the autocomplete criterion
 */
void autocomplete(trie_t *trie, char *prefix, int criterion);

#endif
