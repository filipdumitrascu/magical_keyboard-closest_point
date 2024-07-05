/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#ifndef ABC_H
#define ABC_H

#include "utils.h"

typedef struct node_t node_t;
struct node_t {
	node_t *left; /* left child */
	node_t *right; /* right child */

	int *coord; /* point's coordinates */
};

typedef struct bst_t bst_t;
struct bst_t {
	node_t  *root; /* root of the tree */
	int size; /* number of points in the tree*/
};

/**
 * @brief The function returns a dynamically allocated
 * node structure with all fields initialized.
 * 
 * @param point the point data
 * @param k dimensions
 * @return node_t* the node
 */
node_t *bst_create_node(int *point, int *k);

/**
 * @brief The function returns a dynamically allocated
 * k-d tree structure with all fields initialized.
 * 
 * @return bst_t* 
 */
bst_t *bst_create_tree(void);

/**
 * @brief The function inserts a new word in the k-d tree.
 * 
 * @param bst the bst
 * @param point the point
 * @param k dimensions
 */
void bst_insert_node(bst_t *bst, int *point, int *k);

/**
 * @brief The function frees the momory used by a node.
 * 
 * @param node th node
 */
void bst_free_subtree(node_t *node);

/**
 * @brief The functions calls recursively the bst_free_subtree
 * function in order to free the entire memory used by the tree.
 * 
 * @param bst the bst
 */
void bst_free_tree(bst_t *bst);

/**
 * @brief The function loads a file given as input and inserts
 * in a k-d tree all the points previously read.
 * 
 * @param bst the bst
 * @param filename the filename
 * @param k dimensions
 */
void load_file(bst_t *bst, char *filename, int *k);

/**
 * 
 * @brief The function calculates the euclidian
 * distance between two points
 * 
 * @param point1 first point
 * @param point2 second point
 * @param k dimensions
 * @return double 
 */
double distance(node_t *point1, node_t *point2, int *k);

/**
 * @brief The function retuns which node is closer to the target node.
 * 
 * @param temp temporary node
 * @param root the root
 * @param target the target
 * @param k dimensions
 * @return node_t* 
 */
node_t *closest(node_t *temp, node_t *root, node_t *target, int *k);

/**
 * @brief The function returns the nearest node to the target node.
 * 
 * @param root the root
 * @param target the target
 * @param k how many dimensions
 * @param depth the depth
 * @return node_t* 
 */
node_t *nn(node_t *root, node_t *target, int *k, int depth);

/**
 * @brief The function checks if the given node is outside the range.
 * 
 * @param node the node
 * @param start the start
 * @param end the end
 * @param k dimensions
 * @return int 
 */
int is_outside_range(node_t *node, int *start, int *end, int *k);

/**
 * @brief The function prints all the points within the given range.
 * 
 * @param root the root
 * @param start the start
 * @param end teh end
 * @param depth the depth
 * @param k dimensions
 */
void rs(node_t *root, int *start, int *end, int depth, int *k);

#endif /* ABC_H_ */
