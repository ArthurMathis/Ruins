//
// Created by Daav on 18/11/2023.
//

#include <cstdlib>
#include "../header/blindMonster.h"

blindMonster::blindMonster(int health, int strength, double hability, std::string type)
    : monster{health, strength, hability, type} {}

void blindMonster::move(const adventurer &adventurer) {
    // Déclaration des variables de coordonnées
    int X, Y;
    // Génération d'un nombre aléatoire entre -1 et 1 pour le déplacement aléatoire
    do {
        X = rand() % 3 - 1;
        Y = rand() % 3 - 1;
    } while(X == 0 && Y == 0); // Nouvelle génération si les deux sont nuls car le monstre doit bouger
    // Déplacement du monstre
    character::move(X,Y);
}