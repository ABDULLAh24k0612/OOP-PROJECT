#include "player.h"

Player::Player() : position(1) {}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int position) {
    this->position = position;
}

void Player::move(int steps) {
    position += steps;
    if (position > 100) position = 100;
}
