#include "doctest.h"
#include "../box.h"

TEST_CASE("[box] Constructions et modifications d'un case") {
    SUBCASE("Création de différents type de case") {
        SUBCASE("Création d'un mur")
        {
            box b{box::BX_WALL};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'un mur avec des pieces")
        {
            int coins = 10;
            box b{box::BX_WALL, coins};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }

        SUBCASE("Création d'un mur avec une amulette")
        {
            box b{box::BX_WALL, 0, true};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'un mur avec une amulette et des pieces")
        {
            int coins = 10;
            box b{box::BX_WALL, coins, true};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }

        SUBCASE("Création d'une case extern")
        {
            box b{box::BX_EXTERN};

            REQUIRE_EQ(b.type(), box::BX_EXTERN);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
        }

        SUBCASE("Création d'une case vide")
        {
            box b{box::BX_ACCESSIBLE};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
        }

        SUBCASE("Création d'une case avec des pieces")
        {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), true);
            REQUIRE_EQ(b.coins(), coins);
        }

        SUBCASE("Création d'une case avec une amulette")
        {
            box b{box::BX_ACCESSIBLE, 0, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'une case avec des pieces et une amulette")
        {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }
    }

    SUBCASE("Manipulation du contenu d'une case")
    {
        SUBCASE("Suppression d'une amulette")
        {
            box b{box::BX_ACCESSIBLE, 0, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.hasAmulet(), true);

            b.removeAmulet();
            REQUIRE_EQ(b.hasAmulet(), false);
        }

        SUBCASE("Suppression de pieces")
        {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.hasCoins(), true);
            REQUIRE_EQ(b.coins(), coins);

            b.removeCoins();
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }
    }
}