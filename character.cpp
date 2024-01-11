//
// Created by Daav on 18/11/2023.
//

#include "character.h"

const std::string character::CHAR_ADVENTURER = "adventurer";
const std::string character::CHAR_MONSTER = "monster";
const std::string character::CHAR_BLINDMONSTER = "blindmonster";

character::character(int health, int strength, std::string type)
    : d_health{health}, d_strength{strength}, d_type{type} {}

int character::health() const {
    return d_health;
}

int character::strength() const {
    return d_strength;
}

coord character::position() const {
    return d_coord;
}

std::string character::type() const {
    return d_type;
}

void character::move(int x, int y) {
    d_coord.moveOn(x,y);
}

bool character::isDead() const {
    return d_health <= 0;
}

void character::getDamaged(int damage) {
    d_health -= damage;
    if (isDead())
        die();
}

void character::die() {
    d_health = 0;
    d_strength = 0;
}


