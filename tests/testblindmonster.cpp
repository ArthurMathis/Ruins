//
// Created by Daav on 23/12/2023.
//
#include "doctest.h"
#include "../character.h"
#include "../adventurer.h"
#include "../monster.h"
#include "../blindMonster.h"
#include <random>

TEST_SUITE("Test des méthodes de la classe blindMonster") {
    TEST_SUITE("Test des constructeurs") {
        SCENARIO("Test du constructeur et des méthodes de récupération") {
            GIVEN("Initialisation d'un blindMonster") {
                int health = 80, strength = 12, hability = 80;
                std::string type = "blindmonster";
                blindMonster monster(health, strength, hability, type);
                THEN("Vérification des données") {
                    REQUIRE_EQ(monster.health(), health);
                    REQUIRE_EQ(monster.strength(), strength);
                    REQUIRE_EQ(monster.hability(), hability);
                    REQUIRE_EQ(monster.type(), type);
                }
            }
        }

        SCENARIO("Test du constructeur par défaut et des méthodes de récupération") {
            GIVEN("Initialisation d'un blindMonster") {
                blindMonster monster{};
                THEN("Vérification des données") {
                    REQUIRE_EQ(monster.health(), blindMonster::DEFAULT_HEALTH);
                    REQUIRE_EQ(monster.strength(), blindMonster::DEFAULT_STRENGTH);
                    REQUIRE_EQ(monster.hability(), blindMonster::DEFAULT_HABILITY);
                    REQUIRE_EQ(monster.type(), "blindmonster");
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes de déplacements") {
        SCENARIO("Test de la méthode move de character") {
            GIVEN("Initialisation d'un monster") {
                blindMonster monster{};
                WHEN("Positionnement du monster") {
                    monster.character::move(1, 1);
                    THEN("Vérification de la position") {
                        coord point{1, 1};
                        REQUIRE_EQ(monster.position(), point);
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement") {
            GIVEN("Initialisation d'un blindMonster et d'un aventurier") {
                blindMonster monster{};
                coord positionInitiale = monster.position();
                WHEN("Calcul d'un déplacement du monstre aveugle et déplacement") {
                    int possibleX[] = {0, 0, -1, 1, -1, 1, -1, 1};
                    int possibleY[] = {1, -1, 0, 0, 1, 1, -1, -1};
                    std::vector<int> directions = {0, 1, 2, 3, 4, 5, 6, 7};
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::shuffle(directions.begin(), directions.end(), gen);

                    monster.character::move(possibleX[directions[0]], possibleY[directions[0]]);

                    THEN("Vérification du déplacement entre -1 et 1") {
                        coord nouvellePosition = monster.position();
                        REQUIRE_GE(nouvellePosition.x(), positionInitiale.x() - 1);
                        REQUIRE_LE(nouvellePosition.x(), positionInitiale.x() + 1);
                        REQUIRE_GE(nouvellePosition.y(), positionInitiale.y() - 1);
                        REQUIRE_LE(nouvellePosition.y(), positionInitiale.y() + 1);
                        REQUIRE_NE(nouvellePosition, positionInitiale);
                    }
                }
            }
        }
    }
}