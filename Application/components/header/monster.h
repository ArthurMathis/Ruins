//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_MONSTER_H
#define QUALITE_DE_PROG_MONSTER_H

#include "character.h"
#include "adventurer.h"

class monster : public character {
public :
    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du monstre
     * @param strength Les points d'attaque du monstre
     * @param hability Son taux d'habilieté au coups critiques
     * @param type Type monstre voyant
     */
    monster(int health = 70, int strength = 5, double hability = 90, std::string type = "monster");
    /**
      * @brief Destructeur par défaut
      */
    virtual ~monster() = default;

    /**
      * @brief Fonction renvoyant le pourcentage d'habilité
      * @return poucentage d'habilité
      */
    int hability() const;

    /**
      * @brief Réecriture de la méthode virtuelle permettant ainsi à un monstre d'attaquer un personnage
      * @param[in] c - Le personnage à attaquer
      */
    void attack(character &c) override;
    /**
      * @brief Réecriture de la méthode virtuelle permettant de gérer la réception d'une attaque par un monstre
      * @param[in] attackStrengthPoints - Points de force de l'attaque
      */
    void hasBeenAttacked(int attackStrengthPoints) override;

    /**
      * @brief Méthode retournant si le joueur est suffisanement proche du monstre
      * @param adventurer l'aventurier
      * @return true si le joueur est proche
      */
    bool isClose(const adventurer &adventurer) const;

    /**
     * @brief Méthode retournant dans quelle direction se situe le joueur
     * @param adventurer l'aventurier
     * @return Un entier représentant la direction
     */
    int direction(const adventurer &adventurer) const;

    /**
     * @brief Méthode virtuelle permettant à un monstre de se déplacer en fonction de l'aventurier
     */
    virtual void move(const adventurer &adventurer);
private:
    /// Pourcentage d'habilité du monstre
    double d_hability;
};

#endif //QUALITE_DE_PROG_MONSTER_H
