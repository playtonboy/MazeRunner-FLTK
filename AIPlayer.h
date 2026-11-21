#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Position.h"
#include "Game.h"

// The algorithmic player (T5). Every turn it answers three questions:
//   1. Where should I go?  -> the nearest treasure, or the exit X when
//                             all 5 treasures are collected
//   2. How do I get there? -> Breadth-First Search (BFS) around the walls
//   3. What is my next step? -> only the FIRST step of that path
// The enemies move after every turn, so the AI searches again every turn.
//
// It only looks at the game through the public functions of Game, exactly
// like the screen does. It never uses fixed treasure positions or a fixed route.
class AIPlayer
{
private:
    bool findFirstStep(const Game& game, bool avoidEnemyNeighbours, char& firstStep) const;
    bool canVisit(const Game& game, Position position, bool avoidEnemyNeighbours) const;
    bool isTarget(const Game& game, Position position) const;
    bool isNextToEnemy(const Game& game, Position position) const;
    char safeStep(const Game& game) const;
public:
    char chooseMove(const Game& game) const;
};

#endif /* AIPLAYER_H_ */
