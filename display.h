#ifndef PROJET_DISPLAY_H
#define PROJET_DISPLAY_H

#include <string>

class display {
public:
    /// Couleurs pour l'affichage.
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string WHITE;
    static const std::string PURPLE;
    static const std::string CYAN;

    /**
     * @brief Affiche la représentation graphique d'un aventurier.
     */
    void displayAdventurer();

    /**
     * @brief Affiche la représentation graphique d'un monstre.
     */
    void displayMonster();

    /**
     * @brief Affiche la représentation graphique d'un monstre aveugle.
     */
    void displayBlindMonster();

    /**
     * @brief Affiche la représentation graphique d'un amulette.
     */
    void displayAmulet();

    /**
     * @brief Affiche la représentation graphique d'un mur.
     */
    void displayWall();

    /**
     * @brief Affiche la représentation graphique d'une case vide.
     */
    void displayEmptyCase();

    /**
     * @brief Affiche la représentation graphique d'une case externe.
     */
    void displayExternCase();

    /**
     * @brief Affiche la représentation graphique d'une pièce de monnaie.
     */
    void displayCoin();
};

#endif // PROJET_DISPLAY_H
