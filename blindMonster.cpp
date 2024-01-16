//
// Created by Daav on 18/11/2023.
//

#include <cstdlib>
#include <random>
#include <algorithm>
#include "blindMonster.h"
#include "display.h"
#include "castle.h"

blindMonster::blindMonster(int health, int strength, double hability, std::string type)
    : monster{health, strength, hability, type} {}

coord blindMonster::generateNewPosition(std::shared_ptr<adventurer> &adventurer) const {
    // Les 8 déplacements possibles
    coord dirs[] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {1, 1}, {-1, -1}, {1, -1}};

    // Récupération d'un index aléatoire dans les directions possibles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 7);
    int idx = distrib(gen);

    coord newPosition{};

    newPosition += dirs[idx];
    newPosition += position();
    return newPosition;
}

void blindMonster::show(display &d) const
{
    d.displayBlindMonster();
}
