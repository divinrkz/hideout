#ifndef __CELL_H__
#define __CELL_H__

#include <stdbool.h>
#include <stdlib.h>

const int grid_width = 25;
const int grid_height = 12;
const int num_cells = grid_width * grid_height;

typedef struct cell
{
    size_t x;
    size_t y;
} cell_t;
/**
 * Updates the adjacency matrix to show current cell and neighbor are directly connected
 * @param cell current cell
 * @param neighbor cell neighbor
 */
void adjacency(cell_t *current, cell_t *neighbor);
/**
 *
 * This function checks if there is a direct connection (adjacency) between two cells, Cell and cellNeighbour.
 * @param cell current cell
 * @param neighbor cell neighbor
 * @param adj_matrix adjancey matrix with direct connections
 * @return true if there is a direct connection between current and neighbor.
 */
bool isAdjacency(cell_t *current, cell_t *neighbor, bool adj_matrix[][num_cells]);

/**
 * Finds a random unvisited neighbor of the current cell.
 * @param cell current cell.
 * @returns NULL if all neighbors are visited. Otherwise, it returns a random unvisited neighbor.
 */
cell_t *get_neighbor(cell_t *current, bool visited[][grid_height + 2]);

#endif // #ifndef __CELL_H__
