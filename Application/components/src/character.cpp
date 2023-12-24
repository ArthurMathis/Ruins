//
// Created by Daav on 18/11/2023.
//

#include "../header/character.h"

const std::string character::CHAR_ADVENTURER = "adventurer";
const std::string character::CHAR_MONSTER = "monster";
const std::string character::CHAR_BLINDMONSTER = "blindmonster";

character::character(int health, int strength, std::string type)
    : d_health{health}, d_strength{strength}, d_type{type} {}

int character::health() const {
    // Renvoi du nombre de points de vie
    return d_health;
}

int character::strength() const {
    // Renvoi du nombre de points de force
    return d_strength;
}

coord character::position() const {
    // Renvoi du point de coordonnées
    return d_coord;
}

std::string character::type() const {
    // Renvoi du type du personnage
    return d_type;
}

void character::move(int x, int y) {
    // Changement des coordonnées du personnage
    d_coord.moveOn(x,y);
}

void character::getDamaged(int damage) {
    // Réception des dégâts par le personnage
    d_health -= damage;

    // Faire mourir le personnage si son nombre de point de vie est inférieur ou égal à 0
    if (isDead())
        die();
}

void character::die() {
    // Mise à zéro des points de vie et de force
    d_health = 0;
    d_strength = 0;
}

bool character::isDead() const {
    // Vérification du nombre de points de vie
    return d_health <= 0;
}


