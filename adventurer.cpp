//
// Created by Daav on 18/11/2023.
//

#include <cstdlib>
#include "adventurer.h"
#include "display.h"

using std::cout;
using std::cin;

adventurer::adventurer(int swordSolidity, int armorSolidity, int coin, int health, int strength, std::string type)
        : character{health, strength, type}, d_coins{coin}, d_sword{swordSolidity},
        d_armor{armorSolidity}, d_amulet{false} {}

int adventurer::coins() const {
    return d_coins;
}

sword adventurer::getSword() const {
    return d_sword;
}

armor adventurer::getArmor() const {
    return d_armor;
}

bool adventurer::amulet() const {
    return d_amulet;
}

void adventurer::attack(character &c) {
    int attackStrength = d_strength + d_sword.solidity();

    // Génération d'un nombre aléatoire entre 0 et 99 et vérification de l'infériorité de ce nombre à la probabilité de multiplication de la puissance
    if ((rand() % 100) < DEFAULT_ATTACKPROBABILITY)
        attackStrength = static_cast<int>(attackStrength * 0.9);

    // Lancement de l'attaque sur le personnage c
    c.hasBeenAttacked(attackStrength);

    if(c.isDead())
    {
        int enemyStrength = c.strength();

        d_strength += static_cast<int>(enemyStrength * 0.25);
        d_health += static_cast<int>(enemyStrength * 0.75);
    }

    d_sword.reduce(1);
}

void adventurer::hasBeenAttacked(int attackStrengthPoints) {
    int armorDamage = static_cast<int>(attackStrengthPoints * 0.75);

    if(d_armor.solidity() < armorDamage)
        armorDamage = d_armor.solidity();

    int adventurerDamage = attackStrengthPoints - armorDamage;

    d_armor.reduce(armorDamage);
    getDamaged(adventurerDamage);
}

void adventurer::info() const {
    cout << "----- INFO AVENTURIER ----" << std::endl;
    cout << "💓: " << health() << " 💪: " << strength() << std::endl;
    cout << "🪙: " << coins() << " 🧿: " << amulet() << std::endl;
    cout << "🗡: " << d_sword.solidity() << " 🛡:" << d_armor.solidity() << std::endl;

    // 🗡 🪙 🧿 🛡
}

void adventurer::show(display &d) const
{
    d.displayAdventurer();
}

void adventurer::addCoins(int numberOfCoin) {
    d_coins += numberOfCoin;
}

void adventurer::takeAmulet() {
    d_amulet = true;
}

void adventurer::repairSword(int coinAmount) {
    d_sword.increase(coinAmount);
    d_coins -= coinAmount;
}

void adventurer::repairArmor(int coinAmount) {
    d_armor.increase(coinAmount);
    d_coins -= coinAmount;
}

void adventurer::reset() {
    d_health = DEFAULT_HEALTH;
    d_strength = DEFAULT_STRENGTH;
    d_coins = DEFAULT_COINS;
    d_amulet = false;
    d_sword.setSolidity(DEFAULT_SWORDSOLIDITY);
    d_armor.setSolidity(DEFAULT_ARMORSOLIDITY);
}
