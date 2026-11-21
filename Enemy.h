#ifndef ENEMY_H_
#define ENEMY_H_

#include "Position.h"

// One enemy: only where it is. Game decides where it moves.
class Enemy 
{
private:
    Position position;
public:
    Enemy();
    Position getPosition() const;
    void setPosition(Position position);
};

#endif /* ENEMY_H_ */
