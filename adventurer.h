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
    /// Constantes par défaut
    static constexpr int DEFAULT_SWORDSOLIDITY = 90;
    static constexpr int DEFAULT_ARMORSOLIDITY = 10;
    static constexpr int DEFAULT_COINS = 0;
    static constexpr int DEFAULT_HEALTH = 100;
    static constexpr int DEFAULT_STRENGTH = 10;
    static constexpr double DEFAULT_ATTACKPROBABILITY = 80.0;

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
     * @brief Fonction renvoyant le nombre de pièces.
     * @return Le nombre de pièces.
     */
    int coins() const;
    /**
     * @brief Récupère l'épée de l'aventurier.
     * @return L'épée de l'aventurier.
     */
    sword getSword() const;
    /**
     * @brief Récupère l'armure de l'aventurier.
     * @return L'armure de l'aventurier.
     */
    armor getArmor() const;
    /**
     * @brief Vérifie si l'aventurier possède un amulette.
     * @return True si l'aventurier possède une amulette, False sinon.
     */
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
     * @brief Affiche les informations de l'aventurier.
     */
    void info() const override;
    /**
     * @brief Affiche l'aventurier dans l'interface graphique.
     * @param d - L'objet de type display responsable de l'affichage.
     */
    void show(display &d) const override;

    /**
      * @brief Méthode permettant à un aventurier de gagner un nombre de pièce
      */
    void addCoins(int numberOfCoin);
    /**
     * @brief Donne une amulette à l'aventurier.
     */
    void takeAmulet();

    /**
     * @brief Répare l'épée de l'aventurier en échange d'un certain montant de pièces.
     * @param coinAmount - Le montant de pièces à payer pour la réparation.
     */
    void repairSword(int coinAmount);
    /**
     * @brief Répare l'armure de l'aventurier en échange d'un certain montant de pièces.
     * @param coinAmount - Le montant de pièces à payer pour la réparation.
     */
    void repairArmor(int coinAmount);

    /**
     * @brief Réinitialise les attributs de l'aventurier à leurs valeurs par défaut.
     */
    void reset() override;
private:
    /// Nombre de pièces possédées par l'aventurier.
    int d_coins;
    /// True si l'aventurier possède une amulette, False sinon.
    bool d_amulet;
    /// Épée de l'aventurier.
    sword d_sword;
    /// Armure de l'aventurier.
    armor d_armor;
};


#endif //QUALITE_DE_PROG_PLAYER_H
