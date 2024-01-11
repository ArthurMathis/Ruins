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

void monster::calculateNewPositionNotBlind(int direction, int &newX, int &newY) {
    newX = position().x();
    newY = position().y();

    // (1): ↑ (2): ↓ (3): → (4): ← (5): ↖ (6): ↗ (7): ↙ (8): ↘
    switch(direction) {
        case 1: newX -= 1; break;
        case 2: newX += 1; break;
        case 3: newY += 1; break;
        case 4: newY -= 1; break;
        case 5: newX -= 1; newY -= 1; break;
        case 6: newX -= 1; newY += 1; break;
        case 7: newX += 1; newY -= 1; break;
        case 8: newX += 1; newY += 1; break;
    }
}

void monster::move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster) {
    if(isClose(adventurer)) {
        int d = direction(adventurer), newX, newY;

        calculateNewPositionNotBlind(d, newX, newY);

        // Vérifier si la nouvelle case est à l'intérieur des limites du château
        if(newX >= 0 && newY >= 0 && newX < castle.d_boxes.size() && newY < castle.d_boxes[0].size()) {
            // Vérifier si la nouvelle case est accessible et que le monstre peut y accéder
            if(castle.d_boxes[newX][newY].accessibility()) {
                // On vérifie ce qu'on a fait du monstre en essayant de le mettre dans la case et on le bouge si nécessaire
                int status = castle.d_boxes[newX][newY].putCharacter(monster);
                
                if(status == box::BX_MOVE_ON_ATTACK || status == box::BX_MOVE)
                {
                    castle.d_boxes[position().x()][position().y()].removeCharacter();
                    character::move(newX, newY);
                }
            }
        }
    }
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

