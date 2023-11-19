#include "player.h"

Player::Player(Colour c): colour{c}, score{0} {}

Colour Player::getColour() const {
    return colour;
}

void Player::setScore(double newScore) {
    score = newScore;
}

double Player::getScore() const {
    return score;
}
