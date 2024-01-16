//
// Created by Daav on 18/11/2023.
//

#include <cstdlib>
#include "monster.h"
#include "castle.h"

monster::monster(int health, int strength, double hability, std::string type)
    : character{health, strength, type}, d_hability{hability}
{}

int monster::hability() const {
    return d_hability;
}

void monster::attack(character &c) {
    int attackStrength = d_strength;
    // Génération d'un nombre aléatoire entre 0 et 99 et vérification de l'infériorité de ce nombre à l'habilité
    if ((rand() % 100) < d_hability)
        attackStrength = static_cast<int>(attackStrength * 0.9);

    // Lancement de l'attaque sur le personnage c
    c.hasBeenAttacked(attackStrength);
}

void monster::hasBeenAttacked(int attackStrengthPoints) {
    int monsterDamage = attackStrengthPoints;
    getDamaged(monsterDamage);
}

bool monster::isClose(std::shared_ptr<adventurer> &adventurer) const {
    int distance = position().distance(adventurer->position());
    return distance < MOVE_TO_PLAYER_DISTANCE;
}

bool monster::isNearInfo(std::shared_ptr<adventurer> &adventurer) const {
    int distance = position().distance(adventurer->position());
    return distance == INFO_DISTANCE;
}

int monster::direction(std::shared_ptr<adventurer> &adventurer) const
{
    // (1): ↑ (2): ↓ (3): → (4): ← (5): ↖ (6): ↗ (7): ↙ (8): ↘
    if(position().y() > adventurer->position().y())
    {
        if(position().x() > adventurer->position().x()) return 5;
        if(position().x() < adventurer->position().x()) return 7;
        return 4;
    }
    else if(position().y() < adventurer->position().y())
    {
        if(position().x() > adventurer->position().x()) return 6;
        if(position().x() < adventurer->position().x()) return 8;
        return 3;
    }
    else
    {
        if(position().x() > adventurer->position().x()) return 1;
    }
    return 2;
}

coord monster::generateNewPosition(std::shared_ptr<adventurer> &adventurer) const {
    if(isClose(adventurer)) {
        int dir = direction(adventurer);
        int newX = position().x();
        int newY = position().y();

        // (1): ↑ (2): ↓ (3): → (4): ← (5): ↖ (6): ↗ (7): ↙ (8): ↘
        switch (dir) {
            case 1:
                newX -= 1;
                break;
            case 2:
                newX += 1;
                break;
            case 3:
                newY += 1;
                break;
            case 4:
                newY -= 1;
                break;
            case 5:
                newX -= 1;
                newY -= 1;
                break;
            case 6:
                newX -= 1;
                newY += 1;
                break;
            case 7:
                newX += 1;
                newY -= 1;
                break;
            case 8:
                newX += 1;
                newY += 1;
                break;
        }
        return {newX, newY};
    }
    return position();
}

void monster::show(display &d) const
{
    d.displayMonster();
}

void monster::reset() {
    d_health = DEFAULT_HEALTH;
    d_strength = DEFAULT_STRENGTH;
}

void monster::info() const
{
    std::cout << "Type : " << type() << std::endl;
    std::cout << "💓: " << health() << " 💪: " << strength() << " 🧠: " << hability() << std::endl;
}

