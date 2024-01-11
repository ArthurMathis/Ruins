//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_BLINDMONSTER_H
#define QUALITE_DE_PROG_BLINDMONSTER_H

#include "monster.h"

class blindMonster : public monster {
public:
    static constexpr int DEFAULT_HEALTH = 70;
    static constexpr int DEFAULT_STRENGTH = 5;
    static constexpr double DEFAULT_HABILITY = 90;

    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du monstre
     * @param strength Les points d'attaque du monstre
     * @param hability Pourcentage d'habilieté du monstre
     * @param type Type monstre aveugle
     */
    blindMonster(int health = DEFAULT_HEALTH, int strength = DEFAULT_STRENGTH, double hability = DEFAULT_HABILITY, std::string type = "blindmonster");

    /**
     * @brief Réecriture de la méthode virtuelle permettant à un monstre aveugle de se déplacer
     */
    void move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster) override;
    void show(display &d) const override;
};


#endif //QUALITE_DE_PROG_BLINDMONSTER_H
