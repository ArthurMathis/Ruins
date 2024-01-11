#include "doctest.h"
#include "../box.h"
#include "../adventurer.h"
#include "../monster.h"

TEST_CASE("[box] Constructions et modifications d'un case") {
    SUBCASE("Création de différents type de case") {
        SUBCASE("Création d'un mur") {
            box b{box::BX_WALL};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'un mur avec des pieces") {
            int coins = 10;
            box b{box::BX_WALL, coins};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }

        SUBCASE("Création d'un mur avec une amulette") {
            box b{box::BX_WALL, 0, true};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'un mur avec une amulette et des pieces") {
            int coins = 10;
            box b{box::BX_WALL, coins, true};

            REQUIRE_EQ(b.type(), box::BX_WALL);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }

        SUBCASE("Création d'une case extern") {
            box b{box::BX_EXTERN};

            REQUIRE_EQ(b.type(), box::BX_EXTERN);
            REQUIRE_EQ(b.accessibility(), false);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
        }

        SUBCASE("Création d'une case vide") {
            box b{box::BX_ACCESSIBLE};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), false);
        }

        SUBCASE("Création d'une case avec des pieces") {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), false);
            REQUIRE_EQ(b.hasCoins(), true);
            REQUIRE_EQ(b.coins(), coins);
        }

        SUBCASE("Création d'une case avec une amulette") {
            box b{box::BX_ACCESSIBLE, 0, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_EQ(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_EQ(b.coins(), 0);
        }

        SUBCASE("Création d'une case avec des pieces et une amulette") {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.accessibility(), true);
            REQUIRE_NE(b.hasAmulet(), true);
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }
    }

    SUBCASE("Manipulation du contenu d'une case") {
        SUBCASE("Suppression d'une amulette") {
            box b{box::BX_ACCESSIBLE, 0, true};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.hasAmulet(), true);

            b.removeAmulet();
            REQUIRE_EQ(b.hasAmulet(), false);
        }

        SUBCASE("Suppression de pieces") {
            int coins = 10;
            box b{box::BX_ACCESSIBLE, coins};

            REQUIRE_EQ(b.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(b.hasCoins(), true);
            REQUIRE_EQ(b.coins(), coins);

            b.removeCoins();
            REQUIRE_EQ(b.hasCoins(), false);
            REQUIRE_NE(b.coins(), coins);
        }
        SUBCASE("Test de la méthode putCharacter")
        {
            SUBCASE("Case vide avec aventurier")
            {
                std::shared_ptr<adventurer> adventurer{};
                box emptyBox(box::BX_ACCESSIBLE);
                int result = emptyBox.putCharacter(adventurer);

                REQUIRE(result == box::BX_MOVE);
                REQUIRE(emptyBox.getCharacter() == adventurer);
            }

            SUBCASE("Case avec monstre attaquant aventurier")
            {
                std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
                std::shared_ptr<monster> existingMonster =std::make_shared<monster>() ;
                box boxWithMonster(box::BX_ACCESSIBLE, 0, false, existingMonster);
                int result = boxWithMonster.putCharacter(adam);

                REQUIRE_EQ(result,box::BX_ATTACK);
            }

            SUBCASE("Case avec monstre et nouvel autre monstre") {
                std::shared_ptr<monster> existingMonster = std::make_shared<monster>();
                std::shared_ptr<monster> newMonster = std::make_shared<monster>();
                box boxWithMonster(box::BX_ACCESSIBLE, 0, false, existingMonster);
                int result = boxWithMonster.putCharacter(newMonster);

                REQUIRE(result == box::BX_AVOID);
                REQUIRE(boxWithMonster.getCharacter() == existingMonster);
            }
        }
        SUBCASE("Test de la méthode putCharacter")
        {

            SUBCASE("Case avec case vide et aventurier")
            {
                SUBCASE("Aventurier ajouté à une case vide")
                {
                    std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
                    box emptyBox(box::BX_ACCESSIBLE);
                    int result = emptyBox.putCharacter(adam);

                    REQUIRE_EQ(result, box::BX_MOVE);
                    REQUIRE_EQ(emptyBox.getCharacter(), adam);
                }

            }

            SUBCASE("Case avec monstre et aventurier")
            {
                SUBCASE("Aventurier ajouté à une case avec monstre")
                {
                    std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
                    std::shared_ptr<monster> existingMonster = std::make_shared<monster>();
                    box boxWithMonster(box::BX_ACCESSIBLE, 0, false, existingMonster);
                    int result = boxWithMonster.putCharacter(adam);

                    REQUIRE_EQ(result, box::BX_ATTACK);
                    REQUIRE_EQ(boxWithMonster.getCharacter(), existingMonster);
                }

            }

            SUBCASE("Case avec monstre et autre monstre")
            {
                SUBCASE("Monstre ajouté à une case avec un monstre existant")
                {
                    std::shared_ptr<monster> existingMonster = std::make_shared<monster>();
                    std::shared_ptr<monster> newMonster = std::make_shared<monster>();
                    box boxWithMonster(box::BX_ACCESSIBLE, 0, false, existingMonster);
                    int result = boxWithMonster.putCharacter(newMonster);

                    REQUIRE_EQ(result, box::BX_AVOID);
                    REQUIRE_EQ(boxWithMonster.getCharacter(), existingMonster);
                }

            }

        }
    }
}
