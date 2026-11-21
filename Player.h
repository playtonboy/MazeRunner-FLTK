#ifndef PLAYER_H_
#define PLAYER_H_

#include "Position.h"

const int START_LIVES = 3;

// Where the player is, how many lives are left and the score.
class Player 
{
private:
    Position position;
    int lives;
    int score;
public:
    Player();
    Position getPosition() const;
    void setPosition(Position position);
    int getLives() const;
    void loseLife();
    int getScore() const;
    void addScore(int points);
};

#endif /* PLAYER_H_ */
