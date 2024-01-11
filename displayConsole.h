#ifndef DISPLAYCONSOLE_H
#define DISPLAYCONSOLE_H

#include "display.h"

class displayConsole : public display {
public:
    /// Couleurs pour l'affichage.
    static const std::string BLACK;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string WHITE;
    static const std::string PURPLE;
    static const std::string CYAN;

    void displayAdventurer() const override;
    void displayMonster() const override;
    void displayBlindMonster() const override;
    void displayAmulet() const override;
    void displayWall() const override;
    void displayEmptyCase() const override;
    void displayExternCase() const override;
    void displayCoin() const override;
};

#endif //DISPLAYCONSOLE_H
