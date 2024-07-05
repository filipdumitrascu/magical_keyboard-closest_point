/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bst.h"

node_t *bst_create_node(int *point, int *k)
{
	/**
	 * Allocates space defensively for the node
	 * and assigns each field of the stucture
	 */
	node_t *node = malloc(sizeof(node_t));
	DIE(!node, "Malloc for node allocation failed");

	node->left = NULL;
	node->right = NULL;

	node->coord = malloc(*k * sizeof(int));
	DIE(!node->coord, "Malloc for node coordinates failed");

	memcpy(node->coord, point, *k * sizeof(int));

	return node;
}

bst_t *bst_create_tree(void)
{
	/**
	 * Allocates space defensively for the bst
	 * and assigns each field of the stucture
	 */
	bst_t *bst = malloc(sizeof(bst_t));
	DIE(!bst, "bst_tree malloc");

	bst->root = NULL;
	bst->size = 0;

	return bst;
}

void bst_insert_node(bst_t *bst, int *point, int *k)
{
	node_t *root = bst->root;
	node_t *parent = root;
	node_t *node = bst_create_node(point, k);

	if (!parent) {
		bst->root = node;
		return;
	}

	int level = 0;

	while (1) {
		if (point[level % *k] >= parent->coord[level % *k]) {
			/**
			 * If a point with identical coordinates as an existing
			 * point wants to be inserted, continues
			 */
			if (point[level % *k] == parent->coord[level % *k]) {
				for (int i = 0; i < *k && i != level % *k; i++) {
					if (point[i] != parent->coord[i])
						break;
				}
				free(node->coord);
				free(node);
				break;
			}

			if (!parent->right) {
				parent->right = node;
				bst->size++;
				break;
			}
			parent = parent->right;
			level++;
			continue;

		} else {
			if (!parent->left) {
				parent->left = node;
				bst->size++;
				break;
			}
			parent = parent->left;
			level++;
			continue;
		}
	}
}

void bst_free_subtree(node_t *node)
{
	if (!node)
		return;

	bst_free_subtree(node->left);
	bst_free_subtree(node->right);

	free(node->coord);
	free(node);
}

void bst_free_tree(bst_t *bst)
{
	/**
	 * The function frees all the nodes starting with the root
	 * and after it the bst structure
	 */
	bst_free_subtree(bst->root);
	free(bst);
}

void load_file(bst_t *bst, char *filename, int *k)
{
	FILE *in = fopen(filename, "rt");
	DIE(!in, "Can't open the ascii file");

	int n;
	fscanf(in, "%d %d", &n, k);

	int *point = malloc(*k * sizeof(int));
	DIE(!point, "Malloc for array of dimensions failed");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < *k; j++)
			fscanf(in, "%d", &point[j]);
		bst_insert_node(bst, point, k);
	}

	free(point);
	fclose(in);
}

double distance(node_t *point1, node_t *point2, int *k)
{
	double sum = 0;
	for (int i = 0; i < *k; i++) {
		double diff = point1->coord[i] - point2->coord[i];
		sum += pow(diff, 2);
	}
	return sqrt(sum);
}

node_t *closest(node_t *node1, node_t *node2, node_t *target, int *k)
{
	if (!node1)
		return node2;

	if (!node2)
		return node1;

	double dist1 = distance(node1, target, k);
	double dist2 = distance(node2, target, k);

	if (dist1 < dist2)
		return node1;
	else
		return node2;
}

node_t *nn(node_t *root, node_t *target, int *k, int depth)
{
	node_t *next = NULL;
	node_t *other = NULL;

	if (!root)
		return NULL;

	/**
	 * Selects the subtrie which can have the nearest neighbour
	 */
	if (target->coord[depth % *k] < root->coord[depth % *k]) {
		next = root->left;
		other = root->right;
	} else {
		next = root->right;
		other = root->left;
	}

	/**
	 * Finds a temporary nearest node and compares it's distance
	 * with the root in order to exclude this subtree or to take it
	 * into account
	 */
	node_t *temp = nn(next, target, k, depth + 1);
	node_t *nearest = closest(temp, root, target, k);

	/**
	 * Checks the other subtree and if it's closer
	 * iterates through it too.
	 */
	if (distance(target, nearest, k) >= target->coord[depth % *k] -
		root->coord[depth % *k]) {
		temp = nn(other, target, k, depth + 1);
		nearest = closest(temp, nearest, target, k);
	}

	return nearest;
}

int is_outside_range(node_t *node, int *start, int *end, int *k)
{
	for (int i = 0; i < *k; i++) {
		if (node->coord[i] < start[i] || node->coord[i] > end[i])
			return 1;
	}
	return 0;
}

void rs(node_t *root, int *start, int *end, int depth, int *k)
{
	if (!root)
		return;

	rs(root->right, start, end, depth + 1, k);

	/**
	 * Check if the current node lies within the given range
	 */
	if (!is_outside_range(root, start, end, k)) {
		for (int i = 0 ; i < *k; i++)
			printf("%d ", root->coord[i]);
		printf("\n");
	}

	rs(root->left, start, end, depth + 1, k);
}
