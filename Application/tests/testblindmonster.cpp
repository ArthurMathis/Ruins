//
// Created by Daav on 23/12/2023.
//
#include "doctest.h"
#include "../components/header/character.h"
#include "../components/header/adventurer.h"
#include "../components/header/monster.h"
#include "../components/header/blindMonster.h"

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
                    REQUIRE_EQ(monster.health(), 70);
                    REQUIRE_EQ(monster.strength(), 5);
                    REQUIRE_EQ(monster.hability(), 90);
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

        SCENARIO("Vérification du calcul de déplacements aléatoires") {
            int x;
            for(int i = 0; i < 100; i++){
                x = rand() % 3 - 1;
                THEN("Généartion"){
                    bool valid {x >= -1 && x <= 1};
                    REQUIRE_EQ(valid, true);
                }
            }
        }

        SCENARIO("Vérification du déplacement") {
            GIVEN("Initialisation d'un blindMonster et d'un aventurier") {
                blindMonster monster{};
                adventurer player{};
                coord positionInitiale = monster.position();
                WHEN("Déplacement du monstre aveugle") {
                    monster.move(player);
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