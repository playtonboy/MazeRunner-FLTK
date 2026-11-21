#include "Player.h"

Player::Player() 
{
    position.row = 0;
    position.col = 0;
    lives = START_LIVES;
    score = 0;
}

Position Player::getPosition() const 
{
    return position;
}

void Player::setPosition(Position position) 
{
    this->position = position;
}

int Player::getLives() const 
{
    return lives;
}

void Player::loseLife() 
{
    if (lives > 0) 
    {
        lives--;
    }
}

int Player::getScore() const 
{
    return score;
}

void Player::addScore(int points) 
{
    score = score + points;
}
