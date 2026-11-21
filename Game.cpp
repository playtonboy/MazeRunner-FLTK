#include <cstdlib>
#include "Game.h"

using namespace std;

const char DIRECTIONS[4] = {'w', 'a', 's', 'd'};

Game::Game() 
{
    turns = 0;
    treasuresCollected = 0;
    won = false;
    lost = false;
    message = "Move with W A S D";
}

void Game::load(const string& filename) 
{
    maze.load(filename);
    player.setPosition(maze.getPlayerStart());
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {
        enemies[i].setPosition(maze.getEnemyStart(i));
    }
}

// The cell next to 'from': w = up, a = left, s = down, d = right.
// Used for the player and for the enemies, so it is written only once.
// Any other key gives back 'from' itself.
Position Game::nextPosition(Position from, char direction) const 
{
    Position next = from;
    if (direction == 'w' || direction == 'W') 
    {
        next.row--;
    } 
    else if (direction == 'a' || direction == 'A')
    {
        next.col--;
    } 
    else if (direction == 's' || direction == 'S') 
    {
        next.row++;
    } 
    else if (direction == 'd' || direction == 'D') 
    {
        next.col++;
    }
    return next;
}

// One full turn. Returns false (and nothing moves) if the move is not allowed.
bool Game::movePlayer(char direction) 
{
    if (isOver()) 
    {
        return false;  // no more moves after winning or losing
    }

    Position current = player.getPosition();
    Position next = nextPosition(current, direction);

    if (next.row == current.row && next.col == current.col) 
    {
        message = "Use W A S D to move";
        return false;  // not a direction key
    }
    // isInside() is checked first: if it is false, isWall() is never
    // called, so we never read outside the grid array.
    if (!maze.isInside(next) || maze.isWall(next)) 
    {
        message = "Invalid move, you stay where you are.";
        return false;
    }

    // The player moves
    player.setPosition(next);
    turns++;
    message = "Move with W A S D";
    checkCell();
    checkCollision();  // did the player walk into an enemy?
    if (isOver()) 
    {
        return true;
    }

    // The enemies move
    moveEnemies();
    checkCollision();  // did an enemy walk into the player?
    return true;
}

// What happens on the cell the player just stepped on.
void Game::checkCell() 
{
    Position position = player.getPosition();
    char symbol = maze.getSymbol(position.row, position.col);

    if (symbol == 'T') 
    {
        player.addScore(TREASURE_POINTS);
        treasuresCollected++;
        maze.clearCell(position);  // the treasure is gone from the map
        message = "Treasure found! +10";
    } 
    else if (symbol == 'X') 
    {
        if (treasuresCollected == TREASURE_COUNT) 
        {
            won = true;
            message = "YOU WIN! All treasures collected.";
        } 
        else 
        {
            message = "Collect all treasures before the exit.";
        }
    }
}

// Each enemy steps to a random free neighbouring cell.
// If no neighbour is free, the enemy stays where it is.
void Game::moveEnemies() 
{
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {
        Position current = enemies[i].getPosition();

        // Collect the cells this enemy may step to
        Position options[4];
        int count = 0;
        for (int d = 0; d < 4; d++) 
        {
            Position next = nextPosition(current, DIRECTIONS[d]);
            if (canEnemyMoveTo(next)) 
            {
                options[count] = next;
                count++;
            }
        }

        if (count > 0) 
        {
            int choice = rand() % count;  // pick one of the free cells
            enemies[i].setPosition(options[choice]);
        }
    }
}

// An enemy may not walk into a wall, out of the maze, onto another
// enemy, or onto the player's start (so you are safe after a hit).
bool Game::canEnemyMoveTo(Position position) const 
{
    if (!maze.isInside(position) || maze.isWall(position)) 
    {
        return false;
    }
    if (isEnemyAt(position)) 
    {
        return false;
    }
    Position start = maze.getPlayerStart();
    if (position.row == start.row && position.col == start.col) 
    {
		return false; // the player is safe at the start
    }
    return true;
}

bool Game::isEnemyAt(Position position) const 
{
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {
        Position enemy = enemies[i].getPosition();
        if (enemy.row == position.row && enemy.col == position.col) 
        {
            return true;
        }
    }
    return false;
}

// If the player and an enemy are on the same cell: lose a life and go
// back to the start. Score and collected treasures are kept.
void Game::checkCollision() {
    if (!isEnemyAt(player.getPosition())) 
    {
        return;
    }
    player.loseLife();
    player.setPosition(maze.getPlayerStart());
    if (player.getLives() <= 0) 
    {
        lost = true;
        message = "GAME OVER - no lives left";
    } 
    else 
    {
        message = "Caught by an enemy! Back to the start.";
    }
}

// What should be shown at (row, col): player first, then enemies,
// then whatever the map has there.
char Game::getSymbol(int row, int col) const 
{
    Position position = player.getPosition();
    if (row == position.row && col == position.col) 
    {
        return 'P';
    }
    Position cell;
    cell.row = row;
    cell.col = col;
    if (isEnemyAt(cell)) 
    {
        return 'E';
    }
    return maze.getSymbol(row, col);
}

int Game::getTurns() const 
{
    return turns;
}

int Game::getScore() const 
{
    return player.getScore();
}

int Game::getLives() const 
{
    return player.getLives();
}

int Game::getTreasuresCollected() const 
{
    return treasuresCollected;
}

int Game::getTreasuresRemaining() const 
{
    return TREASURE_COUNT - treasuresCollected;
}

bool Game::isOver() const 
{
    return won || lost;
}

bool Game::hasWon() const 
{
    return won;
}

string Game::getMessage() const 
{
    return message;
}
