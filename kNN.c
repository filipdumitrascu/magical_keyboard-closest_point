/* Copyright 2023 < 312CA Dumitrascu Filip Teodor > */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int main(void)
{
	int finish = 0, k;
	char *command, *filename;
	bst_t *bst = bst_create_tree();

	/**
	 *  As long as the exit string has not been received as input,
	 *  call the specific function to each command.
	 *
	 *  To not define a guessed constant representing the maximum
	 *  number of letters a command can have, reads with %ms
	 *  to dynamically allocate them until space.
	 */
	while (!finish) {
		scanf("%ms", &command);

		if (!strcmp(command, "LOAD")) {
			scanf("%ms", &filename);
			load_file(bst, filename, &k);
			free(filename);

		} else if (!strcmp(command, "NN")) {
			int *input_point = malloc(k * sizeof(int));
			DIE(!input_point, "Malloc for input_point failed");

			for (int i = 0; i < k; i++)
				scanf("%d", &input_point[i]);

			node_t *target = bst_create_node(input_point, &k);
			node_t *nearest = nn(bst->root, target, &k, 0);

			for (int i = 0 ; i < k; i++)
				printf("%d ", nearest->coord[i]);
			printf("\n");

			free(target->coord);
			free(target);
			free(input_point);

		} else if (!strcmp(command, "RS")) {
			int *start = malloc(k * sizeof(int));
			DIE(!start, "Malloc for start range failed");

			int *end = malloc(k * sizeof(int));
			DIE(!end, "Malloc for end rage failed");

			int a = 0, b = 0;
			for (int i = 0; i < 2 * k; i++) {
				if (i % 2) {
					scanf("%d", &end[a]);
					a++;
				} else {
					scanf("%d", &start[b]);
					b++;
				}
			}

			rs(bst->root, start, end, 0, &k);

			free(start);
			free(end);

		} else {
			bst_free_tree(bst);
			finish = 1;
		}

		free(command);
	}
	return 0;
}
