#include "doctest.h"
#include "../display.h"

TEST_CASE("[display] Tests des fonctions de la classe display")
{
    display objetAffichage;

    SUBCASE("Test de displayAdventurer()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayAdventurer();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "A");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayMonster()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayMonster();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "M");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayBlindMonster()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayBlindMonster();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "m");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayWall()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayWall();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "#");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayEmptyCase()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayEmptyCase();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "_");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayExternCase()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayExternCase();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "X");

        std::cout.rdbuf(old);
    }

    SUBCASE("Test de displayCoin()")
    {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        objetAffichage.displayCoin();

        std::string sortie = buffer.str();
        REQUIRE_EQ(sortie, "o");

        std::cout.rdbuf(old);
    }
}