//
// Created by Daav on 18/11/2023.
//
#ifndef QUALITE_DE_PROG_adventurer_H
#define QUALITE_DE_PROG_adventurer_H

#include "character.h"
#include "sword.h"
#include "armor.h"
#include <string>

using std::string;

class adventurer : public character {
public:
    /**
     * @brief Constructeur par valeurs
     * @param swordSolidity - Solidité de l'épée
     * @param armorSolidity - Solidité de l'armure
     * @param coin - Nombre de pièce
     * @param health - Points de vie
     * @param strength - Points de force
     */
    adventurer(int swordSolidity = 90, int armorSolidity = 10, int coin = 0, int health = 100, int strength = 10, std::string type = "adventurer");

    /**
     * @brief Méthdoe retournant l'armure du joueur
     * @return
     */
    armor getArmor() const;
    /**
     * @brief Méthode retournant l'épée du joueur
     * @return
     */
    sword getSword() const;

    /**
      * @brief Fonction renvoyant le nombre de pièces
      * @return nombre de pièces
      */
    int coins() const;

    /**
      * @brief Réecriture de la méthode virtuelle permettant ainsi à un aventurier d'attaquer un personnage
      * @param[in] c - Le personnage à attaquer
      */
    void attack(character &c) override;
    /**
      * @brief Réecriture de la méthode virtuelle permettant de gérer la réception d'une attaque par un aventurier
      * @param[in] attackStrength - Points de force de l'attaque
      */
    void hasBeenAttacked(int attackStrength) override;

    /**
     * @brief Fonction renvoyant le choix de déplacement de l'utilisateur
     * @return la valeur correspondant au choix de déplacement
     */
    // int moveChoice();
    /**
      * @brief Réecriture de la méthode virtuelle permettant ainsi à un aventurer de se déplacer
      */
    // void move() override;

    /**
      * @brief Méthode permettant à un aventurier de gagner un nombre de pièce
      */
    void addCoins(int numberOfCoin);

private:
    int d_coins;
    sword d_sword;
    armor d_armor;
};


#endif //QUALITE_DE_PROG_PLAYER_H
