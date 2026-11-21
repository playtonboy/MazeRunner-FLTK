#include <queue>
#include "AIPlayer.h"

using namespace std;

// The four moves, in the same order for every search.
const char MOVES[4] = {'w', 'a', 's', 'd'};
const int ROW_CHANGE[4] = {-1, 0, 1, 0};   // w = up, s = down
const int COL_CHANGE[4] = {0, -1, 0, 1};   // a = left, d = right

// One turn of the AI: returns the key it "presses" (w, a, s or d).
char AIPlayer::chooseMove(const Game& game) const
{
    char step;

    // Safer idea from the practical: avoid enemies AND the cells next to them.
    if (findFirstStep(game, true, step))
    {
        return step;
    }
    // Not possible? Then only treat the enemy cells themselves as walls.
    if (findFirstStep(game, false, step))
    {
        return step;
    }
    // No path at all right now (enemies are in the way): take a safe step
    // and search again next turn, when the enemies have moved.
    return safeStep(game);
}

// Breadth-First Search from the player to the nearest target.
// The queue is the "waiting line": take from the FRONT, add to the BACK.
// Because the cells come out ring by ring (1 move away, then 2, then 3, ...),
// the first target that is taken out is the nearest one.
// Returns true and puts the first move of the route in firstStep if a target
// was found, false if no target can be reached.
bool AIPlayer::findFirstStep(const Game& game, bool avoidEnemyNeighbours, char& firstStep) const
{
    bool seen[MAZE_SIZE][MAZE_SIZE];        // already added to the queue?
    Position cameFrom[MAZE_SIZE][MAZE_SIZE]; // the cell we came from
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            seen[r][c] = false;
        }
    }

    Position start = game.getPlayerPosition();
    queue<Position> waiting;
    waiting.push(start);
    seen[start.row][start.col] = true;

    while (!waiting.empty())
    {
        Position current = waiting.front();  // first in, first out
        waiting.pop();

        // STOP when a target is taken out of the queue
        if (isTarget(game, current))
        {
            // Follow "came from" backwards until the cell right after the
            // start: that cell is the first step of the shortest route.
            Position step = current;
            while (cameFrom[step.row][step.col].row != start.row
                || cameFrom[step.row][step.col].col != start.col)
            {
                step = cameFrom[step.row][step.col];
            }
            // Which key moves the player from start to step?
            for (int d = 0; d < 4; d++)
            {
                if (start.row + ROW_CHANGE[d] == step.row && start.col + COL_CHANGE[d] == step.col)
                {
                    firstStep = MOVES[d];
                }
            }
            return true;
        }

        // Add every open neighbour that was not seen yet to the BACK of the queue
        for (int d = 0; d < 4; d++)
        {
            Position next;
            next.row = current.row + ROW_CHANGE[d];
            next.col = current.col + COL_CHANGE[d];
            if (canVisit(game, next, avoidEnemyNeighbours) && !seen[next.row][next.col])
            {
                seen[next.row][next.col] = true;
                cameFrom[next.row][next.col] = current;
                waiting.push(next);
            }
        }
    }
    return false;  // the queue is empty and no target was found
}

// May the search go through this cell? Walls and enemies count as walls,
// and if avoidEnemyNeighbours is true, the cells next to an enemy as well.
bool AIPlayer::canVisit(const Game& game, Position position, bool avoidEnemyNeighbours) const
{
    // Inside is checked first, so getSymbol() never reads outside the grid
    if (position.row < 0 || position.row >= MAZE_SIZE
        || position.col < 0 || position.col >= MAZE_SIZE)
    {
        return false;
    }
    char symbol = game.getSymbol(position.row, position.col);
    if (symbol == '#' || symbol == 'E')
    {
        return false;
    }
    if (avoidEnemyNeighbours && isNextToEnemy(game, position))
    {
        return false;
    }
    return true;
}

// Question 1, where should I go: a treasure while there are treasures left,
// otherwise the exit.
bool AIPlayer::isTarget(const Game& game, Position position) const
{
    char symbol = game.getSymbol(position.row, position.col);
    if (game.getTreasuresRemaining() > 0)
    {
        return symbol == 'T';
    }
    return symbol == 'X';
}

// Is there an enemy on one of the four cells around this position?
bool AIPlayer::isNextToEnemy(const Game& game, Position position) const
{
    for (int d = 0; d < 4; d++)
    {
        int row = position.row + ROW_CHANGE[d];
        int col = position.col + COL_CHANGE[d];
        if (row >= 0 && row < MAZE_SIZE && col >= 0 && col < MAZE_SIZE
            && game.getSymbol(row, col) == 'E')
        {
            return true;
        }
    }
    return false;
}

// When no path exists: step to a free cell, preferably one that is not next
// to an enemy. The game has no "wait" move, so the AI always has to step.
char AIPlayer::safeStep(const Game& game) const
{
    Position start = game.getPlayerPosition();
    char backup = MOVES[0];
    bool hasBackup = false;

    for (int d = 0; d < 4; d++)
    {
        Position next;
        next.row = start.row + ROW_CHANGE[d];
        next.col = start.col + COL_CHANGE[d];
        if (canVisit(game, next, true))
        {
            return MOVES[d];  // free and away from the enemies
        }
        if (!hasBackup && canVisit(game, next, false))
        {
            backup = MOVES[d];  // free, but next to an enemy
            hasBackup = true;
        }
    }
    if (hasBackup)
    {
        return backup;
    }
    // Walled in by enemies: any move that is not into a wall
    for (int d = 0; d < 4; d++)
    {
        int row = start.row + ROW_CHANGE[d];
        int col = start.col + COL_CHANGE[d];
        if (row >= 0 && row < MAZE_SIZE && col >= 0 && col < MAZE_SIZE
            && game.getSymbol(row, col) != '#')
        {
            return MOVES[d];
        }
    }
    return MOVES[0];
}
