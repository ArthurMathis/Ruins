//
// Created by Daav on 23/12/2023.
//

#include "doctest.h"
#include "../components/header/character.h"
#include "../components/header/adventurer.h"
#include "../components/header/monster.h"

TEST_SUITE("Test des méthodes de la classe monster") {
    TEST_SUITE("Test des constructeurs") {
        SCENARIO("Test du constructeur et des méthodes de récupération") {
            GIVEN("Initialisation d'un monster") {
                int health = 80, strength = 12, hability = 80;
                std::string type = "monster";
                monster monster(health, strength, hability, type);
                THEN("Vérification des données") {
                    REQUIRE_EQ(monster.health(), health);
                    REQUIRE_EQ(monster.strength(), strength);
                    REQUIRE_EQ(monster.hability(), hability);
                    REQUIRE_EQ(monster.type(), type);
                }
            }
        }

        SCENARIO("Test du constructeur par défaut et des méthodes de récupération") {
            GIVEN("Initialisation d'un monster") {
                monster monster{};
                THEN("Vérification des données") {
                    REQUIRE_EQ(monster.health(), 70);
                    REQUIRE_EQ(monster.strength(), 5);
                    REQUIRE_EQ(monster.hability(), 90);
                    REQUIRE_EQ(monster.type(), "monster");
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes d'attaque, de réception d'attaque et de mort") {
        SCENARIO("Test de la méthode attack sur un monstre") {
            GIVEN("Initialisation de deux monsters") {
                monster monster1{}, monster2{};
                WHEN("Réalisation de l'attaque") {
                    monster1.attack(monster2);
                    THEN("Vérification de l'attaque") {
                        bool valid {
                            monster2.health() == 70 - monster1.strength() ||
                            monster2.health() == 70 - static_cast<int>(0.9 * monster1.strength())
                        };
                        REQUIRE_EQ(valid, true);
                    }
                }
            }
        }

        SCENARIO("Test de la méthode getDamaged") {
            GIVEN("Initialisation d'un monster") {
                monster monster{100};
                WHEN("Infligation de dégâts") {
                    int degats = 20;
                    monster.getDamaged(degats);
                    THEN("Vérification des données") {
                        REQUIRE_EQ(monster.health(), 100 - degats);
                    }
                }
            }
        }

        SCENARIO("Test de la méthode hasBeenAttacked") {
            GIVEN("Initialisation d'un monster") {
                monster monster{};
                WHEN("Infligation de dégâts") {
                    int degats = 20;
                    monster.hasBeenAttacked(degats);
                    THEN("Vérification des données") {
                        REQUIRE_EQ(monster.health(), 70 - degats);
                    }
                }
            }
        }

        SCENARIO("Test de la méthode die"){
            GIVEN("Initialisation de deux monsters") {
                monster monster1{100, 120, 90};
                monster monster2{100,20, 30};
                WHEN("Réalisation de l'attaque") {
                    monster1.attack(monster2);
                    THEN("Vérification de la mort") {
                        REQUIRE_EQ(monster2.isDead(), true);
                    }
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes de déplacements") {
        SCENARIO("Test de la méthode move de character") {
            GIVEN("Initialisation d'un monster") {
                monster monster{};
                WHEN("Positionnement du monster") {
                    monster.character::move(1, 1);
                    THEN("Vérification de la position") {
                        coord point{1, 1};
                        REQUIRE_EQ(monster.position(), point);
                    }
                }
            }
        }

        SCENARIO("Test de validation de la fonction isClose") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player") {
                    player.move(1, 1);
                    THEN("Vérification de la fonction") {
                        REQUIRE_EQ(monster.isClose(player), true);
                    }
                }
            }
        }

        SCENARIO("Test de non validation de la fonction isClose") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player") {
                    player.move(12, 13);
                    THEN("Vérification de la fonction") {
                        REQUIRE_EQ(monster.isClose(player), false);
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 1") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(1, 0);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 1);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{1, 2};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 2") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(1, 2);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 2);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{1, 0};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 3") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(2, 1);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 3);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{2, 1};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 4") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(0, 1);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 4);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{0, 1};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 5") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(0, 0);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 5);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{0, 2};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 6") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(2, 0);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 6);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{2, 2};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 7") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(0, 2);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 7);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{0, 0};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du déplacement direction 8") {
            GIVEN("Initialisation d'un monster et d'un adventurer") {
                adventurer player{};
                monster monster{};
                WHEN("Positionnement du player et du monster") {
                    player.move(2, 2);
                    monster.character::move(1, 1);
                    THEN("Vérification de la fonction direction") {
                        REQUIRE_EQ(monster.direction(player), 8);
                        WHEN("Déplacement du monstre") {
                            monster.move(player);
                            THEN("Vérification de la position") {
                                coord point{2, 0};
                                REQUIRE_EQ(monster.position(), point);
                            }
                        }
                    }
                }
            }
        }
    }
}