#include "doctest.h"
#include "../display.h"
#include <iostream>
#include <sstream>

TEST_CASE("[display] Tests des fonctions de la classe display")
{
    display objetAffichage;

    SUBCASE("Test de displayAdventurer()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayAdventurer();

        std::string sortie = oss.str();
        // Vérifier si la sortie contient "P" et la couleur blanche
        REQUIRE(sortie.find("P") != std::string::npos);
        REQUIRE(sortie.find(display::WHITE) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayMonster()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayMonster();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "M" et la couleur rouge
        REQUIRE(sortie.find("M") != std::string::npos);
        REQUIRE(sortie.find(display::RED) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayBlindMonster()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayBlindMonster();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "W" et la couleur violette
        REQUIRE(sortie.find("W") != std::string::npos);
        REQUIRE(sortie.find(display::PURPLE) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayAmulet()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayAmulet();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "A" et la couleur cyan
        REQUIRE(sortie.find("A") != std::string::npos);
        REQUIRE(sortie.find(display::CYAN) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayWall()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayWall();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "#" et la couleur noire
        REQUIRE(sortie.find("#") != std::string::npos);
        REQUIRE(sortie.find(display::BLACK) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayEmptyCase()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayEmptyCase();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient un espace (case vide)
        REQUIRE(sortie.find(" ") != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayExternCase()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayExternCase();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "X" et la couleur verte
        REQUIRE(sortie.find("X") != std::string::npos);
        REQUIRE(sortie.find(display::GREEN) != std::string::npos);

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayCoin()")
    {
        std::ostringstream oss;
        std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

        objetAffichage.displayCoin();

        std::string sortie = oss.str();

        // Vérifier si la sortie contient "O" et la couleur jaune
        REQUIRE(sortie.find("O") != std::string::npos);
        REQUIRE(sortie.find(display::YELLOW) != std::string::npos);

        std::cout.rdbuf(old);
    }
}
