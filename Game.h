#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "Maze.h"
#include "Player.h"
#include "Enemy.h"

const int TREASURE_COUNT = 5;    // every maze has exactly 5 treasures
const int TREASURE_POINTS = 10;  // points for one treasure

// The rules of the game. Game owns the Maze, the Player and the Enemies.
// One turn = the player moves one cell, then every enemy moves one cell.
// It knows nothing about FLTK, so the same class would also work in a
// terminal version (or with an AI choosing the moves).
class Game 
{
private:
    Maze maze;
    Player player;
    Enemy enemies[ENEMY_COUNT];
    int turns;               // number of valid moves (turns) so far
    int treasuresCollected;
    bool won;
    bool lost;
    std::string message;     // what happened in the last turn

    Position nextPosition(Position from, char direction) const;
    void checkCell();
    void moveEnemies();
    bool canEnemyMoveTo(Position position) const;
    bool isEnemyAt(Position position) const;
    void checkCollision();
public:
    Game();
    void load(const std::string& filename);
    bool movePlayer(char direction);
    char getSymbol(int row, int col) const;
    int getTurns() const;
    int getScore() const;
    int getLives() const;
    int getTreasuresCollected() const;
    int getTreasuresRemaining() const;
    bool isOver() const;
    bool hasWon() const;
    std::string getMessage() const;
};

#endif /* GAME_H_ */
