#include "Enemy.h"

Enemy::Enemy() 
{
    position.row = 0;
    position.col = 0;
}

Position Enemy::getPosition() const 
{
    return position;
}

void Enemy::setPosition(Position position) 
{
    this->position = position;
}
