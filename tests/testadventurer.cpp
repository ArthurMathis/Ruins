//
// Created by Daav on 22/12/2023.
//

#include <sstream>
#include "doctest.h"
#include "../character.h"
#include "../adventurer.h"
#include "../monster.h"

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

    SCENARIO("Test de la récupération de l'épée") {
        GIVEN("Initialisation d'un aventurier") {
            adventurer player{};
            WHEN("Récupération de l'épée") {
                sword playerSword = player.getSword();
                THEN("Vérification de la solidité de l'épée") {
                    REQUIRE_EQ(playerSword.solidity(), adventurer::DEFAULT_SWORDSOLIDITY);
                }
            }
        }
    }

    SCENARIO("Test de la récupération de l'armure") {
        GIVEN("Initialisation d'un aventurier") {
            adventurer player{};
            WHEN("Récupération de l'armure") {
                armor playerArmor = player.getArmor();
                THEN("Vérification de la solidité de l'armure") {
                    REQUIRE_EQ(playerArmor.solidity(), adventurer::DEFAULT_ARMORSOLIDITY);
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

    SCENARIO("Test de la méthode reset") {
        GIVEN("Initialisation d'un aventurier avec des valeurs") {
            int swordSolidity = 60, armorSolidity = 30, coins = 8, health = 75, strength = 20;
            adventurer player(swordSolidity, armorSolidity, coins, health, strength);
            WHEN("Appel de la méthode reset") {
                player.reset();
                THEN("Vérification des données réinitialisées") {
                    REQUIRE_EQ(player.coins(), adventurer::DEFAULT_COINS);
                    REQUIRE_EQ(player.health(), adventurer::DEFAULT_HEALTH);
                    REQUIRE_EQ(player.strength(), adventurer::DEFAULT_STRENGTH);
                    REQUIRE_FALSE(player.amulet());
                    sword playerSword = player.getSword();
                    REQUIRE_EQ(playerSword.solidity(), adventurer::DEFAULT_SWORDSOLIDITY);
                    armor playerArmor = player.getArmor();
                    REQUIRE_EQ(playerArmor.solidity(), adventurer::DEFAULT_ARMORSOLIDITY);
                }
            }
        }
    }

    SCENARIO("Test de la méthode takeAmulet") {
        GIVEN("Initialisation d'un aventurier") {
            adventurer player{};
            WHEN("Appel de la méthode takeAmulet") {
                player.takeAmulet();
                THEN("Vérification que l'aventurier a une amulette") {
                    REQUIRE_EQ(player.amulet(), true);
                }
            }
        }
    }

    TEST_SUITE("Test des méthodes de réparations") {
        SCENARIO("Test de la méthode repairSword") {
            GIVEN("Initialisation d'un aventurier et ajout de pièces") {
                adventurer player{};
                int coinAmount = 5;
                player.addCoins(coinAmount);
                int previousCoin = player.coins();
                WHEN("Appel de la méthode repairSword") {
                    player.repairSword(coinAmount);
                    THEN("Vérification que l'épée est réparée et les pièces retirées") {
                        sword repairedSword = player.getSword();
                        REQUIRE_EQ(repairedSword.solidity(), adventurer::DEFAULT_SWORDSOLIDITY + coinAmount);
                        REQUIRE_EQ(player.coins(), previousCoin - coinAmount);
                    }
                }
            }
        }

        SCENARIO("Test de la méthode repairArmor") {
            GIVEN("Initialisation d'un aventurier et ajout de pièces") {
                adventurer player{};
                int coinAmount = 5;
                player.addCoins(coinAmount);
                int previousCoin = player.coins();
                WHEN("Appel de la méthode repairArmor") {
                    player.repairArmor(coinAmount);
                    THEN("Vérification que l'armure est réparée et les pièces retirées") {
                        armor repairedArmor = player.getArmor();
                        REQUIRE_EQ(repairedArmor.solidity(), adventurer::DEFAULT_ARMORSOLIDITY + coinAmount);
                        REQUIRE_EQ(player.coins(), previousCoin - coinAmount);
                    }
                }
            }
        }
    }

    SCENARIO("Test de la méthode info pour Adventurer") {
        GIVEN("Initialisation d'un aventurier") {
            adventurer player{};
            std::ostringstream output;
            WHEN("Appel de la méthode info") {
                std::streambuf* coutStream = std::cout.rdbuf();
                std::cout.rdbuf(output.rdbuf());
                player.info();
                std::cout.rdbuf(coutStream);
                THEN("Vérification du texte affiché") {
                    std::string expectedOutput = "----- INFO AVENTURIER ----\n"
                                                 "💓: " + std::to_string(player.health()) +
                                                 " 💪: " + std::to_string(player.strength()) + "\n"
                                                 "🪙: " + std::to_string(player.coins()) +
                                                 " 🧿: " + std::to_string(player.amulet()) + "\n"
                                                 "🗡: " + std::to_string(player.getSword().solidity()) +
                                                 " 🛡:" + std::to_string(player.getArmor().solidity()) + "\n";
                    REQUIRE_EQ(output.str(), expectedOutput);
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
                        REQUIRE_EQ(player.health(), adventurer::DEFAULT_HEALTH - degats);
                    }
                }
            }
        }

        TEST_SUITE("Test de la méthode attack") {
            SCENARIO("Test de la mise à mort d'un monstre") {
                GIVEN("Création d'un Aventurier et d'un monstre") {
                    adventurer player{};
                    monster monster{2};
                    WHEN("Réalisation d'une attaque") {
                        player.attack(monster);
                        THEN("Vérifications") {
                            REQUIRE_EQ(monster.isDead(), true);
                            REQUIRE_EQ(player.getSword().solidity(), adventurer::DEFAULT_SWORDSOLIDITY - 1);
                            int expectedNewStrength = static_cast<int>(monster.strength() * 0.25);
                            REQUIRE_EQ(player.strength(), adventurer::DEFAULT_STRENGTH + expectedNewStrength);
                            int expectedNewHealth = static_cast<int>(monster.strength() * 0.75);
                            REQUIRE_EQ(player.health(), adventurer::DEFAULT_HEALTH + expectedNewHealth);
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégat de la méthode attack") {
                GIVEN("Création d'un Aventurier et d'un monstre") {
                    adventurer player{};
                    monster monster{};
                    WHEN("Réalisation d'une attaque") {
                        player.attack(monster);
                        THEN("Vérifications") {
                            bool valid{
                                    monster.health() == monster::DEFAULT_HEALTH - (player.strength() + adventurer::DEFAULT_SWORDSOLIDITY) ||
                                    monster.health() == monster::DEFAULT_HEALTH - static_cast<int>((player.strength() + adventurer::DEFAULT_SWORDSOLIDITY) * 0.9)
                            };
                            REQUIRE_EQ(valid, true);
                            REQUIRE_EQ(player.getSword().solidity(), adventurer::DEFAULT_SWORDSOLIDITY - 1);
                        }
                    }
                }
            }
        }

        TEST_SUITE("Test de la méthode hasBeenAttacked") {
            SCENARIO("Test de la mise à mort d'un aventurier") {
                GIVEN("Création d'un Aventurier") {
                    adventurer player{};
                    int attackStrength = 1000;
                    WHEN("Réception d'une attaque") {
                        player.hasBeenAttacked(attackStrength);
                        THEN("Vérification des dégâts") {
                            REQUIRE_EQ(player.isDead(), true);
                        }
                    }
                }
            }

            SCENARIO("Vérification de la casse d'une armure") {
                GIVEN("Création d'un Aventurier") {
                    adventurer player{};
                    int attackStrength = 150;
                    WHEN("Réception d'une attaque") {
                        player.hasBeenAttacked(attackStrength);
                        THEN("Vérification des dégâts") {
                            REQUIRE_EQ(player.getArmor().solidity(), 0);
                        }
                    }
                }
            }

            SCENARIO("Vérification du taux de dégat encaissé par l'armure et par le player") {
                GIVEN("Création d'un Aventurier") {
                    adventurer player{};
                    int attackStrength = monster::DEFAULT_STRENGTH;  // Utilisation de la force du joueur pour simuler la force du monstre
                    WHEN("Réception d'une attaque") {
                        player.hasBeenAttacked(attackStrength);
                        GIVEN("Calculs des dégâts") {
                            // Déclaration des variables de l'armure
                            int expectedArmorDamage = static_cast<int>(attackStrength * 0.75);
                            int expectedAdventurerDamage = attackStrength - expectedArmorDamage;
                            THEN("Vérification des dégâts") {
                                REQUIRE_EQ(player.getArmor().solidity(), adventurer::DEFAULT_ARMORSOLIDITY - expectedArmorDamage);
                                REQUIRE_EQ(player.health(), adventurer::DEFAULT_HEALTH - expectedAdventurerDamage);
                            }
                        }
                    }
                }
            }
        }
    }
}
