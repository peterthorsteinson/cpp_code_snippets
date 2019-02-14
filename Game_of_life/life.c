// In theory, the Game of Life is played out on an infinite grid.
// This implementation provides two alternatives that can be commented out or uncommented in:
// 1. A finite wrap-around grid that continues on opposite edges (modulo arithmetic indexes).
//    -> Uncomment the call to get_neighbors_wrap and comment the call to get_neighbors_no_wrap
// 2. A finite hard-edged grid without without wrap-around.
//    -> Uncomment the call to get_neighbors_no_wrap and comment the call to get_neighbors_wrap

#include <stdlib.h>
#include <stdio.h>
#include "life.h"

/*
 * get_grid creates new memory for a "grid".
 * x is the height and y is the width.
 */
char** get_grid(int x, int y) {
	int i;
	// allocate space for data
	char *data = malloc(sizeof(char) * x * y);
	// create array of pointers to first elem in each 2D row
	char **ptr_array = malloc(sizeof(char*) * x);
	for (i = 0; i < x; i++) {
		ptr_array[i] = data + (i*y);
	}
	return ptr_array;
}

/*
 * print_grid attempts to print an x height
 * by y width grid stored at the location
 * provided by grid
 */
void print_grid(int x, int y, char** grid) {
	for (int i = 0; i < x; i++)	{
		for (int j = 0; j < y; j++)	{
			printf("%02X ", (char)grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid
 * is returned.
 */
char** mutate(int x, int y, char** grid) {
	// Every cell interacts with its eight neighbours
	// that are horizontally, vertically, or diagonally adjacent

	char** new_grid = get_grid(x, y); // creates new blank slate to be updated

	// grid points to previous game state, new_grid points to new game state
	// update new game state according to rules applied to previous game state
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			// count live neighbors
			// NOTE: comment out one of the following lines and uncomment the other
			int live_neighbors = get_neighbors_wrap(i, j, x, y, grid);
			//int live_neighbors = get_neighbors_no_wrap(i, j, x, y, grid);

			// copy element from old game state as starting value and then see if it changes
			new_grid[i][j] = grid[i][j];

			// if current cell is live
			if (grid[i][j] != 0) {
				// live cell with < 2 live neighbors dies
				if (live_neighbors < 2) new_grid[i][j] = 0;

				// live cell with > 3 live neighbors dies

				if (live_neighbors > 3) new_grid[i][j] = 0;

				// live cell with 2 or 3 live lives

				if (live_neighbors == 2 || live_neighbors == 2) new_grid[i][j] = 1;

			}
			// else current cell is dead
			else {
				// dead cell with 3 live neighbors becomes live
				if (live_neighbors == 3) new_grid[i][j] = 1;
			}
		}
	}

	// no longer need previous game state so free related heap allocations
	free(*grid); // free the memory that contains the actual data rows
	free(grid);  // free the memory that contains the pointers to the data rows

	return new_grid; // return pointer to newly updated game state
}

// modulo increment
int mi(int i, int n) {
	return ((i + 1) % n);           // modulo arithmetic to wrap edges
}

// modulo decrement
int md(int i, int n) {
	return (i % n - 1 % n + n) % n; // modulo arithmetic to wrap edges
}

/* get_neighbors_wrap is a helper method that returns the number
 * of live neighbors a cell has with wrapping of opposite edges.
 */
int get_neighbors_wrap(int i, int j, int x, int y, char** grid) {
	// Each cell has 8 neighbors
	// Each edge wraps around at opposite edge (modulo arithmetic)
	int live_neighbors = 0;

	// 3 neighbors on row above cell
	if (grid[md(i, x)][md(j, y)] > 0) live_neighbors++;   // test cell up-left
	if (grid[md(i, x)][j]        > 0) live_neighbors++;   // test cell up
	if (grid[md(i, x)][mi(j, y)] > 0) live_neighbors++;   // test cell up-right
	
	// 2 neighbors on same row as cell
	if (grid[i][md(j, y)]        > 0) live_neighbors++;   // test cell left
	if (grid[i][mi(j, y)]        > 0) live_neighbors++;   // test cell right

	// 3 neighbors on row below cell
	if (grid[mi(i, x)][md(j, y)] > 0) live_neighbors++;   // test cell down-left
	if (grid[mi(i, x)][j]        > 0) live_neighbors++;   // test cell down
	if (grid[mi(i, x)][mi(j, y)] > 0) live_neighbors++;   // test cell down-right

	return live_neighbors;
}

/* get_neighbors_no_wrap is a helper method that returns the number
 * of live neighbors a cell has without wrapping of opposite edges.
 */
int get_neighbors_no_wrap(int i, int j, int x, int y, char** grid) {
	// Each cell has 8 neighbors
	// Each edge does not wrap around at opposite edge (no modulo arithmetic)

	int live_neighbors = 0;

	// 3 neighbors on row above cell
	if (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] > 0) live_neighbors++;   // test cell up-left
	if (i - 1 >= 0 && grid[i - 1][j] > 0) live_neighbors++;   // test cell up
	if (i - 1 >= 0 && j + 1 < y  && grid[i - 1][j + 1] > 0) live_neighbors++;   // test cell up-right

	// 2 neighbors on same row as cell
	if (j - 1 >= 0 && grid[i][j - 1] > 0) live_neighbors++;     // test cell left
	if (j + 1 < y             && grid[i][j + 1] > 0) live_neighbors++;     // test cell right

	// 3 neighbors on row below cell
	if (i + 1 < x && j - 1 >= 0 && grid[i + 1][j - 1] > 0) live_neighbors++;    // test cell down-left
	if (i + 1 < x              && grid[i + 1][j] > 0)   live_neighbors++;    // test cell down
	if (i + 1 < x && j + 1 < y   && grid[i + 1][j + 1] > 0) live_neighbors++;    // test cell down-right

	return live_neighbors;
}
