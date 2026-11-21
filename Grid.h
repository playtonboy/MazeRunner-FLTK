#ifndef GRID_H_
#define GRID_H_

#include <FL/Fl_Box.H>
#include "Block.h"
#include "Game.h"

const int GRID_SIZE = MAZE_SIZE * BLOCK_SIZE;  // 20 * 30 = 600 pixels

// The whole maze on screen: a 20 x 20 table of Blocks.
class Grid : public Fl_Box 
{
private:
    Block* blocks[MAZE_SIZE][MAZE_SIZE];
    void createGrid(const Game& game);
public:
    Grid(int x, int y, const Game& game);
    void update(const Game& game);
};

#endif /* GRID_H_ */
