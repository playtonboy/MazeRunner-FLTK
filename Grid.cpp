#include "Grid.h"

Grid::Grid(int x, int y, const Game& game) : Fl_Box(x, y, GRID_SIZE, GRID_SIZE) 
{
    this->box(FL_FLAT_BOX);
    this->color(FL_GRAY);
    createGrid(game);
}

// Makes one Block per cell. Block (row, col) is placed col * 30 pixels to
// the right and row * 30 pixels down from the top-left corner of the grid.
void Grid::createGrid(const Game& game) 
{
    for (int row = 0; row < MAZE_SIZE; row++) 
    {
        for (int col = 0; col < MAZE_SIZE; col++) 
        {
            int blockX = x() + col * BLOCK_SIZE;
            int blockY = y() + row * BLOCK_SIZE;
            blocks[row][col] = new Block(blockX, blockY, game.getSymbol(row, col));
        }
    }
}

// Called after every move: each block shows what is now at its cell.
void Grid::update(const Game& game) 
{
    for (int row = 0; row < MAZE_SIZE; row++) 
    {
        for (int col = 0; col < MAZE_SIZE; col++) 
        {
            blocks[row][col]->setSymbol(game.getSymbol(row, col));
        }
    }
}
