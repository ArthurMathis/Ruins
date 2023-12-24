//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_BLINDMONSTER_H
#define QUALITE_DE_PROG_BLINDMONSTER_H

#include "monster.h"

class blindMonster : public monster {
public:
    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du monstre
     * @param strength Les points d'attaque du monstre
     * @param hability Pourcentage d'habilieté du monstre
     * @param type Type monstre aveugle
     */
    blindMonster(int health = 70, int strength = 5, double hability = 90, std::string type = "blindmonster");

    /**
     * @brief Réecriture de la méthode virtuelle permettant à un monstre aveugle de se déplacer
     */
    void move(const adventurer &adventurer) override;
};


#endif //QUALITE_DE_PROG_BLINDMONSTER_H
