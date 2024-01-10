//
// Created by Daav on 18/11/2023.
//
#ifndef QUALITE_DE_PROG_adventurer_H
#define QUALITE_DE_PROG_adventurer_H

#include "character.h"
#include "sword.h"
#include "armor.h"
#include <string>

#include "display.h"

using std::string;

class adventurer : public character {
public:
    static constexpr int DEFAULT_SWORDSOLIDITY = 90;
    static constexpr int DEFAULT_ARMORSOLIDITY = 10;
    static constexpr int DEFAULT_COINS = 0;
    static constexpr int DEFAULT_HEALTH = 100;
    static constexpr int DEFAULT_STRENGTH = 10;

    /**
     * @brief Constructeur par valeurs
     * @param swordSolidity - Solidité de l'épée
     * @param armorSolidity - Solidité de l'armure
     * @param coin - Nombre de pièce
     * @param health - Points de vie
     * @param strength - Points de force
     */
    adventurer(int swordSolidity = DEFAULT_SWORDSOLIDITY,
               int armorSolidity = DEFAULT_ARMORSOLIDITY,
               int coin = DEFAULT_COINS,
               int health = DEFAULT_HEALTH,
               int strength = DEFAULT_STRENGTH,
               std::string type = "adventurer");

    /**
      * @brief Fonction renvoyant le nombre de pièces
      * @return nombre de pièces
      */
    int coins() const;
    sword getSword() const;
    armor getArmor() const;
    bool amulet() const;

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
    void show(display &d) const override;

    void takeAmulet();
    void repairSword(int coinAmount);
    void repairArmor(int coinAmount);
    void reset() override;
    void info() const override;

private:
    int d_coins;
    bool d_amulet;
    sword d_sword;
    armor d_armor;
};


#endif //QUALITE_DE_PROG_PLAYER_H
