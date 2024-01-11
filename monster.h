//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_MONSTER_H
#define QUALITE_DE_PROG_MONSTER_H

#include "character.h"
#include "adventurer.h"
#include "monster.h"
#include <memory>

class castle;
class monster : public character {
public :
    static constexpr int DEFAULT_HEALTH = 100;
    static constexpr int DEFAULT_STRENGTH = 10;
    static constexpr int INFO_DISTANCE = 1;
    static constexpr int MOVE_TO_PLAYER_DISTANCE = 8;
    static constexpr double DEFAULT_HABILITY = 90;

    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du monstre
     * @param strength Les points d'attaque du monstre
     * @param hability Son taux d'habilieté au coups critiques
     * @param type Type monstre voyant
     */
    monster(int health = DEFAULT_HEALTH, int strength = DEFAULT_STRENGTH, double hability = DEFAULT_HABILITY, std::string type = "monster");
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
    bool isClose(std::shared_ptr<adventurer> &adventurer) const;

    bool isNearInfo(std::shared_ptr<adventurer> &adventurer) const;

    void calculateNewPositionNotBlind(int direction, int &newX, int &newY);

    /**
     * @brief Méthode retournant dans quelle direction se situe le joueur
     * @param adventurer l'aventurier
     * @return Un entier représentant la direction
     */
    int direction(std::shared_ptr<adventurer> &adventurer) const;

    /**
     * @brief Méthode virtuelle permettant à un monstre de se déplacer en fonction de l'aventurier
     */
    virtual void move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster);

    void show(display &d) const override;

    void reset() override;

    void info() const override;
private:
    /// Pourcentage d'habilité du monstre
    double d_hability;
};

#endif //QUALITE_DE_PROG_MONSTER_H
