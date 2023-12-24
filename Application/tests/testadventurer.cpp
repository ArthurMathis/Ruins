//
// Created by Daav on 22/12/2023.
//

#include "doctest.h"
#include "../components/header/character.h"
#include "../components/header/adventurer.h"
#include "../components/header/monster.h"

TEST_SUITE("Test des méthodes de la classe adventurer") {
    TEST_SUITE("Test des constructeurs") {
        SCENARIO("Test du constructeur et des méthodes de récupération") {
            GIVEN("Initialisation d'un aventurier") {
                int swordSolidity = 80, armorSolidity = 20, coins = 5, health = 90, strength = 15;
                std::string type = "adventurer";
                adventurer player(swordSolidity, armorSolidity, coins, health, strength, type);
                THEN("Vérification des données") {
                    REQUIRE_EQ(player.coins(), coins);
                    REQUIRE_EQ(player.health(), health);
                    REQUIRE_EQ(player.strength(), strength);
                    REQUIRE_EQ(player.type(), type);
                }
            }
        }

        SCENARIO("Test du constructeur par défaut et des méthodes de récupération") {
            GIVEN("Initialisation d'un aventurier") {
                adventurer player{};
                THEN("Vérification des données") {
                    REQUIRE_EQ(player.coins(), 0);
                    REQUIRE_EQ(player.health(), 100);
                    REQUIRE_EQ(player.strength(), 10);
                    REQUIRE_EQ(player.type(), "adventurer");
                }
            }
        }
    }

    SCENARIO("Test de l'ajout de pièces") {
        GIVEN("Initialisation d'un aventurier") {
            adventurer player{};
            WHEN("Ajout de pièces") {
                int pieces = 10;
                player.addCoins(pieces);
                THEN("Vérification des pièces ajoutées") {
                    REQUIRE_EQ(player.coins(), pieces);
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes d'attaque, de réception d'attaque et de mort") {
        SCENARIO("Test de la méthode getDamaged") {
            GIVEN("Initialisation d'un aventurier") {
                adventurer player{};
                WHEN("Infligation de dégâts") {
                    int degats = 20;
                    player.getDamaged(degats);
                    THEN("Vérification des données") {
                        REQUIRE_EQ(player.health(), 100 - degats);
                    }
                }
            }
        }

        TEST_SUITE("Test de la méthode attack"){
            SCENARIO("Test de la mise à mort d'un monstre"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    adventurer player{};
                    monster monster{};
                    WHEN("Réalisation d'une attaque"){
                        player.attack(monster);
                        THEN("Vérification des dégâts"){
                            REQUIRE_EQ(monster.isDead(), true);
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégat de la méthode attack"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    // Valeurs par défauts
                    int life = 120, swordDammage = 90;
                    adventurer player{};
                    monster monster{life};
                    WHEN("Réalisation d'une attaque"){
                        player.attack(monster);
                        THEN("Vérification des dégâts"){
                            bool valid{
                                monster.health() == life - player.strength() + swordDammage ||
                                        monster.health() == life - static_cast<int>((player.strength() + swordDammage) * 0.9)
                            };
                            REQUIRE_EQ(valid, true);
                        }
                    }
                }
            }
        }

        TEST_SUITE("Test de la méthode hasBeenAttacked"){
            SCENARIO("Test de la mise à mort d'un aventurier"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    adventurer player{};
                    monster monster{70, 1000};
                    WHEN("Réalisation d'une attaque"){
                        monster.attack(player);
                        THEN("Vérification des dégâts"){
                            REQUIRE_EQ(player.isDead(), true);
                        }
                    }
                }
            }

            SCENARIO("Vérification de la casse d'une armure"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    adventurer player{};
                    monster monster{70, 300};
                    WHEN("Réalisation d'une attaque"){
                        monster.attack(player);
                        THEN("Vérification des dégâts"){
                            REQUIRE_EQ(player.getArmor().solidity(), 0);
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégat encaisser par l'amure et par le player"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    adventurer player{};
                    monster monster{};
                    WHEN("Réalisation d'une attaque"){
                        int solidity = player.getArmor().solidity();
                        int life = player.health();
                        monster.attack(player);
                        GIVEN("Calculs des dégâts"){
                            // Déclaration des variables de l'armure
                            int newSolidity = player.getArmor().solidity();
                            int normalAttack = static_cast<int>(monster.strength() * 0.75 * 0.9);
                            int goodAttack = static_cast<int>(monster.strength() * 0.75);
                            bool validArmor{
                                newSolidity == solidity - normalAttack || newSolidity == solidity - goodAttack
                            };

                            // Déclaration des variables du joueur
                            int newLife = player.health();
                            bool validPlayer{
                                newLife == life - static_cast<int>(normalAttack / 3.0) ||
                                newLife == life - static_cast<int>(goodAttack / 3.0)
                            };
                            THEN("Vérification des dégâts"){
                                REQUIRE_EQ(validArmor, true);
                                REQUIRE_EQ(validPlayer, true);
                            }
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégat encaisser par l'amure et par le player"){
                GIVEN("Création d'un Aventurier et d'un monstre"){
                    adventurer player{};
                    monster monster{70, 50};
                    WHEN("Réalisation d'une attaque"){
                        int solidity = player.getArmor().solidity();
                        int life = player.health();
                        monster.attack(player);
                        GIVEN("Calculs des dégâts"){
                            int normalAttack = static_cast<int>(monster.strength() * 0.75 * 0.9);
                            int goodAttack = static_cast<int>(monster.strength() * 0.75);
                            bool valid{
                                
                            };
                        }
                    }
                }
            }
        }
    }
}
