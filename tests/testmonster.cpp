//
// Created by Daav on 23/12/2023.
//

#include "doctest.h"
#include "../character.h"
#include "../adventurer.h"
#include "../monster.h"
#include "../castle.h"

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
                    REQUIRE_EQ(monster.health(), monster::DEFAULT_HEALTH);
                    REQUIRE_EQ(monster.strength(), monster::DEFAULT_STRENGTH);
                    REQUIRE_EQ(monster.hability(), monster::DEFAULT_HABILITY);
                    REQUIRE_EQ(monster.type(), "monster");
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes d'attaque, de réception d'attaque et de mort") {
        TEST_SUITE("Test de la méthode attack") {
            SCENARIO("Test de la mise à mort d'un aventurier") {
                GIVEN("Création d'un Aventurier et d'un monstre") {
                    adventurer player{};
                    monster monster{70, 1000};
                    WHEN("Réalisation d'une attaque") {
                        monster.attack(player);
                        THEN("Vérification des dégâts") {
                            REQUIRE_EQ(player.isDead(), true);
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégats encaissé par l'amure et par le player") {
                GIVEN("Création d'un Aventurier et d'un monstre") {
                    adventurer player{};
                    monster monster{};
                    WHEN("Réalisation d'une attaque") {
                        int solidity = player.getArmor().solidity();
                        int life = player.health();
                        int monsterStrength = monster.strength();
                        monster.attack(player);
                        GIVEN("Calculs des dégâts") {
                            // Déclaration des variables de l'armure
                            int newSolidity = player.getArmor().solidity();
                            int armorNormalAttack = static_cast<int>(monsterStrength * 0.75 * 0.9);
                            int armorGoodAttack = static_cast<int>(monsterStrength * 0.75);
                            bool validArmor{
                                    newSolidity == solidity - armorNormalAttack || newSolidity == solidity - armorGoodAttack
                            };

                            // Déclaration des variables du joueur
                            int newLife = player.health();
                            int adventurerNormalDamage = monsterStrength - armorNormalAttack;
                            int adventurerGoodDamage = monsterStrength - armorGoodAttack;
                            bool validPlayer{
                                    newLife == life - adventurerNormalDamage ||
                                    newLife == life - adventurerGoodDamage
                            };
                            THEN("Vérification des dégâts") {
                                REQUIRE_EQ(validArmor, true);
                                REQUIRE_EQ(validPlayer, true);
                            }
                        }
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
                        REQUIRE_EQ(monster.health(), monster::DEFAULT_HEALTH - degats);
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

    SCENARIO("Test de la méthode reset pour monster") {
        GIVEN("Initialisation d'un monstre avec des valeurs") {
            int health = 75, strength = 20;
            monster monstre{health, strength};
            WHEN("Appel de la méthode reset") {
                monstre.reset();
                THEN("Vérification des données réinitialisées") {
                    REQUIRE_EQ(monstre.health(), monster::DEFAULT_HEALTH);
                    REQUIRE_EQ(monstre.strength(), monster::DEFAULT_STRENGTH);
                }
            }
        }
    }

    SCENARIO("Test de la méthode info pour Monster") {
        GIVEN("Initialisation d'un monstre") {
            monster enemy{};
            std::ostringstream output;
            WHEN("Appel de la méthode info") {
                std::streambuf* coutStream = std::cout.rdbuf();
                std::cout.rdbuf(output.rdbuf());
                enemy.info();
                std::cout.rdbuf(coutStream);
                THEN("Vérification du texte affiché") {
                    std::string expectedOutput = "Type : " + enemy.type() + "\n"
                                                 "💓: " + std::to_string(enemy.health()) +
                                                 " 💪: " + std::to_string(enemy.strength()) +
                                                 " 🧠: " + std::to_string(enemy.hability()) + "\n";
                    REQUIRE_EQ(output.str(), expectedOutput);
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes de déplacements") {
        std::shared_ptr<adventurer> player = std::make_unique<adventurer>();
        monster monster{};
        SCENARIO("Test de la méthode move de character") {
            WHEN("Positionnement du monster") {
                monster.character::move(1, 1);
                THEN("Vérification de la position") {
                    coord point{1, 1};
                    REQUIRE_EQ(monster.position(), point);
                }
            }
        }

        SCENARIO("Test de validation de la fonction isClose") {
            WHEN("Positionnement du player et du monstre") {
                player->move(1, 1);
                monster.character::move(0,0);
                THEN("Vérification de la fonction") {
                    REQUIRE_EQ(monster.isClose(player), true);
                }
            }
        }

        SCENARIO("Test de non validation de la fonction isClose") {
            WHEN("Positionnement du player et du monstre") {
                player->move(12, 13);
                monster.character::move(0, 0);
                THEN("Vérification de la fonction") {
                    REQUIRE_EQ(monster.isClose(player), false);
                }
            }
        }

        SCENARIO("Test de validation de la fonction isNearInfo") {
            WHEN("Positionnement du player et du monstre") {
                player->move(1, 1);
                monster.character::move(0, 0);
                THEN("Vérification de la fonction") {
                    REQUIRE_EQ(monster.isNearInfo(player), true);
                }
            }
        }

        SCENARIO("Test de non validation de la fonction isNearInfo") {
            WHEN("Positionnement du player et du monstre") {
                player->move(12, 13);
                monster.character::move(0, 0);
                THEN("Vérification de la fonction") {
                    REQUIRE_EQ(monster.isNearInfo(player), false);
                }
            }
        }


        coord expectedPoint{0, 0};
        SCENARIO("Vérification du calcul de déplacement direction 1") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(1, 0);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 1);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers le haut") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 2") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(-1, 0);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 2);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers le bas") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 3") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(0, -1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 3);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers la droite") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 4") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(0, 1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 4);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers la gauche") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 5") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(1, 1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 5);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers en haut à gauche") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 6") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(1, -1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 6);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers en haut à droite") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 7") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(-1, 1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 7);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers en bas à gauche") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }

        SCENARIO("Vérification du calcul de déplacement direction 8") {
            WHEN("Positionnement du player et du monster") {
                player->move(0, 0);
                monster.character::move(-1, -1);
                THEN("Vérification de la fonction direction") {
                    int direction = monster.direction(player);
                    REQUIRE_EQ(direction, 8);
                    WHEN("Calcul des nouvelles positions") {
                        int newX, newY;
                        monster.calculateNewPositionNotBlind(direction,newX,newY);
                        THEN("Vérification de la position après déplacement vers en bas à droite") {
                            REQUIRE_EQ(newX, expectedPoint.x());
                            REQUIRE_EQ(newY, expectedPoint.y());
                        }
                    }
                }
            }
        }
    }
}