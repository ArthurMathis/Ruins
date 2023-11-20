//
// Created by Arthur Mathis on 20/11/2023.
//
#include "doctest.h"
#include "../components/header/point.h"
#include "../components/header/blindMonster.h"

TEST_SUITE("Vérification de la class blindMonster"){
    SCENARIO("Vérification de la class character") {
        GIVEN("Initialisation d'un blindMonster") {
            blindMonster bm{};
            THEN("Test des points de vie et de la force d'attaque") {
                REQUIRE_EQ(bm.healthPoints(), 100);
                REQUIRE_EQ(bm.strengthPoints(), 10);
            }
        }
    }

    TEST_SUITE("Vérification des constructeurs de la classe blindMonster"){
        SCENARIO("Test du constructeur par défault"){
            GIVEN("Initialisation d'un blindMonster"){
                blindMonster bm{};
                THEN("Test des données de base"){
                    REQUIRE_EQ(bm.getSymbol(), 'B');
                    REQUIRE_EQ(bm.getNature(), "Monstre Aveugle");
                    REQUIRE_EQ(bm.healthPoints(), 100);
                    REQUIRE_EQ(bm.strengthPoints(), 10);
                    REQUIRE_EQ(bm.habilityPercentage(), 90);
                }
            }
        }

        SCENARIO("Test du constructeur par valeurs"){
            GIVEN("Initialisation d'un blindMonster"){
                int healthPoints = 240, strenghtPoints = 132, hability = 55;
                blindMonster bm{healthPoints, strenghtPoints, hability};
                THEN("Test du symbole, de la nature, du pourentage d'habilieté, des points de vie et de la force d'attaque"){
                    REQUIRE_EQ(bm.getSymbol(), 'B');
                    REQUIRE_EQ(bm.getNature(), "Monstre Aveugle");
                    REQUIRE_EQ(bm.healthPoints(), healthPoints);
                    REQUIRE_EQ(bm.strengthPoints(), strenghtPoints);
                    REQUIRE_EQ(bm.habilityPercentage(), hability);
                }
            }
        }
    }

    TEST_SUITE("Vérification des fonctions d'attaque, de défense et de mort"){
        SCENARIO("Test de la fonction getAttacked"){
            GIVEN("Initialisation d'un blindMonster"){
                blindMonster bm{};
                WHEN("Réalisation de l'attaque"){
                    int attaque = 23;
                    bm.getAttacked(attaque);
                    THEN("Attaque réalisée"){
                        REQUIRE_EQ(bm.healthPoints(), 100-23);
                    }
                }
            }
        }

        SCENARIO("Test de la fonction attack"){
            GIVEN("Initialisation de deux monsters"){
                blindMonster m1{}, m2{};
                WHEN("Réalisation de l'attaque"){
                    m1.attack(m2);
                    THEN("Attaque réussie"){
                        bool valid {m2.healthPoints() == 100 - m1.strengthPoints() ||
                                    m2.healthPoints() == 100 - 0.9 * m1.strengthPoints()};
                        REQUIRE_EQ(valid, true);
                    }
                }
            }
        }

        SCENARIO("Test de la fonction die"){
            GIVEN("Initialisation de deux monsters"){
                blindMonster m1{100, 120, 90}, m2{100,20, 30};
                WHEN("Réalisation de l'attaque"){
                    m1.attack(m2);
                    THEN("Vérification de la mort"){
                        REQUIRE_EQ(m2.isDead(), true);
                    }
                }
            }
        }
    }

    TEST_SUITE("Test des fonctions de déplacement"){
        SCENARIO("vérification du calcul de déplacements aléatoires"){
            int x;
            for(int i = 0; i < 100; i++){
                x = rand() % 3 - 1;
                THEN("Généartion"){
                    bool valid {x >= -1 && x <= 1};
                    REQUIRE_EQ(valid, true);
                }
            }
        }

        SCENARIO("Vérifcation du déplacement"){
            GIVEN("Calcul d'un déplacement et initialisation d'un blindMonster"){
                int x{rand() % 3 - 1}, y{rand() % 3 - 1};
                blindMonster bm{};
                WHEN("Déplacement du blindMonster"){
                    bm.MoveElement(x, y);
                    THEN("Vérification des coordonnées"){
                        REQUIRE_EQ(bm.getX(), x);
                        REQUIRE_EQ(bm.getY(), y);
                    }
                }
            }
        }
    }
}