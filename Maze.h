#ifndef MAZE_H_
#define MAZE_H_

#include <string>
#include "Position.h"

using namespace std;

const int MAZE_SIZE = 20;
const int ENEMY_COUNT = 3;   

// The map: walls, empty cells, treasures, enemies and the exit.
// It loads itself from a .txt file and checks that the file is usable.
class Maze 
{
private:
    char grid[MAZE_SIZE][MAZE_SIZE];
    Position playerStart;
    Position enemyStarts[ENEMY_COUNT];
    void validate();
public:
    Maze();
    void load(const string& filename);
    Position getPlayerStart() const;
    Position getEnemyStart(int index) const;
    char getSymbol(int row, int col) const;
    bool isInside(Position position) const;
    bool isWall(Position position) const;
    void clearCell(Position position);
};

#endif /* MAZE_H_ */
