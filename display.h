#ifndef PROJET_DISPLAY_H
#define PROJET_DISPLAY_H

#include <string>

class display {
public:
    /**
     * @brief Affiche la représentation graphique d'un aventurier.
     */
    virtual void displayAdventurer() const = 0;

    /**
     * @brief Affiche la représentation graphique d'un monstre.
     */
    virtual void displayMonster() const = 0;

    /**
     * @brief Affiche la représentation graphique d'un monstre aveugle.
     */
    virtual void displayBlindMonster() const = 0;

    /**
     * @brief Affiche la représentation graphique d'un amulette.
     */
    virtual void displayAmulet() const = 0;

    /**
     * @brief Affiche la représentation graphique d'un mur.
     */
    virtual void displayWall() const = 0;

    /**
     * @brief Affiche la représentation graphique d'une case vide.
     */
    virtual void displayEmptyCase() const = 0;

    /**
     * @brief Affiche la représentation graphique d'une case externe.
     */
    virtual void displayExternCase() const = 0;

    /**
     * @brief Affiche la représentation graphique d'une pièce de monnaie.
     */
    virtual void displayCoin() const = 0;
};

#endif // PROJET_DISPLAY_H
