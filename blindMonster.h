//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_BLINDMONSTER_H
#define QUALITE_DE_PROG_BLINDMONSTER_H

#include "monster.h"

class blindMonster : public monster {
public:
    /// Constantes par défaut
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
     * @param castle - Le château où se déplace le monstre.
     * @param adventurer - L'aventurier.
     * @param monster - Le monstre aveugle.
     */
    void move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster) override;

    /**
     * @brief Affiche le monstre aveugle dans l'interface graphique.
     * @param d - L'objet de type display responsable de l'affichage.
     */
    void show(display &d) const override;
};


#endif //QUALITE_DE_PROG_BLINDMONSTER_H
