#include "../character.h"
#include "../adventurer.h"
#include "../monster.h"
#include "../castle.h"
#include"doctest.h"
#include "../blindMonster.h"
#include <vector>
#include <algorithm>

TEST_CASE("Test de la classe castle") {
    castle myCastle;

    std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
    std::vector<std::shared_ptr<monster>> monsters;

    SUBCASE("Test d'initialisation du château")
    {
        myCastle.init(adam, monsters);

        // Vérifiez si l'aventurier est correctement placé
        REQUIRE_EQ(myCastle.d_boxes[adam->position().x()][adam->position().y()].getCharacter(), adam);

        // Vérifiez si les monstres sont correctement placés
        for (const auto &monster: monsters) {
            REQUIRE_EQ(myCastle.d_boxes[monster->position().x()][monster->position().y()].getCharacter(), monster);
        }
    }

    SUBCASE("Test de sauvegarde et chargement du château") {
        myCastle.init(adam, monsters);

        // Sauvegarde du château dans un fichier temporaire
        std::string tempFilename = "tempCastle.txt";
        myCastle.save(tempFilename);

        // Création d'un nouveau château
        castle loadedCastle;
        loadedCastle.load(tempFilename, adam, monsters);

        // Vérifiez si l'état après le chargement est identique à l'état avant la sauvegarde
        //REQUIRE_EQ(std::equal(myCastle.d_boxes.begin(), myCastle.d_boxes.end(),loadedCastle.d_boxes.begin(), loadedCastle.d_boxes.end()),true);
    }

    SUBCASE("Test de la méthode typeCode") {
        castle myCastle;

        SUBCASE("Test avec une case mur") {
            box wallBox(box::BX_WALL);
            std::string result = myCastle.typeCode(wallBox);
            REQUIRE_EQ(result, "W");
        }

        SUBCASE("Test avec une case externe") {
            box externBox(box::BX_EXTERN);
            std::string result = myCastle.typeCode(externBox);
            REQUIRE_EQ(result, "E");
        }

        SUBCASE("Test avec une case accessible vide")
        {
            box emptyBox(box::BX_ACCESSIBLE);
            std::string result = myCastle.typeCode(emptyBox);
            REQUIRE_EQ(result, "R");
        }

        SUBCASE("Test avec une case accessible contenant des pièces")
        {
            box coinsBox(box::BX_ACCESSIBLE, 5);
            std::string result = myCastle.typeCode(coinsBox);
            REQUIRE_EQ(result, "C5");
        }

        SUBCASE("Test avec une case accessible contenant une amulette")
        {
            box amuletBox(box::BX_ACCESSIBLE, 0, true);
            std::string result = myCastle.typeCode(amuletBox);
            REQUIRE_EQ(result, "A");
        }

        SUBCASE("Test avec une case accessible contenant un aventurier")
        {
            std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
            box adventurerBox(box::BX_ACCESSIBLE, 0, false, adam);
            std::string result = myCastle.typeCode(adventurerBox);
            REQUIRE_EQ(result, "P");
        }

        SUBCASE("Test avec une case accessible contenant un monstre")
        {
            std::shared_ptr<monster> mon = std::make_shared<monster>();
            box monsterBox(box::BX_ACCESSIBLE, 0, false, mon);
            std::string result = myCastle.typeCode(monsterBox);
            REQUIRE_EQ(result, "M");
        }

        SUBCASE("Test avec une case accessible contenant un monstre aveugle") {
            std::shared_ptr<blindMonster> Bmon = std::make_shared<blindMonster>();
            box blindMonsterBox(box::BX_ACCESSIBLE, 0, false, Bmon);
            std::string result = myCastle.typeCode(blindMonsterBox);
            REQUIRE_EQ(result, "B");
        }
    }
    SUBCASE("Test de boxFromType")
    {
        castle myCastle;
        std::vector<std::shared_ptr<monster>> monsters;
        std::shared_ptr<adventurer> adam = std::make_shared<adventurer>();
        SUBCASE("Test avec une case mur") {

            box result = myCastle.boxFromType("W", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_WALL);
        }

        SUBCASE("Test avec une case externe") {
            box result = myCastle.boxFromType("E", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_EXTERN);
        }

        SUBCASE("Test avec une case accessible contenant des pièces") {
            box result = myCastle.boxFromType("C5", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(result.coins(), 5);
        }

        SUBCASE("Test avec une case accessible contenant une amulette") {
            box result = myCastle.boxFromType("A", adam,monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
            REQUIRE(result.hasAmulet());
        }

        SUBCASE("Test avec une case accessible vide") {
            box result = myCastle.boxFromType("R", adam,monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
        }

        SUBCASE("Test avec une case accessible contenant un aventurier") {
            box result = myCastle.boxFromType("P", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(result.getCharacter(), adam);
        }

        SUBCASE("Test avec une case accessible contenant un monstre") {
            std::shared_ptr<monster> mon = std::make_shared<monster>();

            box result = myCastle.boxFromType("M", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(result.getCharacter(), monsters.back());
        }

        SUBCASE("Test avec une case accessible contenant un monstre aveugle") {
            std::shared_ptr<blindMonster> Bmon = std::make_shared<blindMonster>();
            box result = myCastle.boxFromType("B", adam, monsters, 0, 0);
            REQUIRE_EQ(result.type(), box::BX_ACCESSIBLE);
            REQUIRE_EQ(result.getCharacter(), monsters.back());
        }
    }

}
