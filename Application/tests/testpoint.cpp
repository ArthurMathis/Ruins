#include "doctest.h"
#include "../components/header/coord.h"

/**
 * @brief Teste la construction des coords et la récupération des coordonnées avec les getters.
 */
TEST_CASE("[coord] Les coords sont bien construits et que les Getter nous renvoyent les coordonnees")
{
    SUBCASE("constructeur par defaut") {
        coord p{};
        int nul = 0;
        REQUIRE_EQ(p.x(), nul);
        REQUIRE_EQ(p.y(), nul);
    }
    SUBCASE("constructeur avec valeur")
    {
        int x = 2;
        int y = 3;
        coord p{x, y};
        REQUIRE_EQ(p.x(), x);
        REQUIRE_EQ(p.y(), y);
    }
}

/**
 * @brief Teste la modification de la position des coords.
 */
TEST_CASE("[coord] Les replacement des coords ")
{
    SUBCASE("modification de la position")
    {
        int x = 2, y = 3;
        coord p{};
        p.moveOn(x, y);
        REQUIRE_EQ(p.x(), x);
        REQUIRE_EQ(p.y(), y);
    }
    SUBCASE("modification de la position à l'aide de coeficient")
    {
        coord p{1, 2};
        p.moveOff(1, 1);
        REQUIRE(p.x() == 2);
        REQUIRE(p.y() == 3);
    }
}

/**
 * @brief Teste les surcharges des opérateurs concernant les coords.
 */
TEST_CASE("[coord] Les surcharges des operateurs concernant les coords ")
{
    SUBCASE("[coord] Les surcharges des operateurs de test d'égalité")
    {
        SUBCASE("[coord] la surcharge  == ")
        {
            coord p1{1, 2};
            coord p2{1, 2};
            REQUIRE_EQ(p1, p2);
        }
        SUBCASE("[coord] La surcharge  =!= ")
        {
            coord p1{1, 2};
            coord p2{3, 2};
            REQUIRE_NE(p1, p2);
        }
    }
    SUBCASE("[coord] Les surcharges de +=")
    {
        coord p1{1, 2};
        coord p2{3, 2};
        coord p3 = p1;
        p1 += p2;
        REQUIRE_EQ(p1.x(), p2.x() + p3.x());
        REQUIRE_EQ(p1.y(), p2.y() + p3.y());
    }
    SUBCASE("[coord] Les surcharges de -=")
    {
        coord p1{2, 2};
        coord p2{1, 1};
        coord p3 = p1;
        p1 -= p2;
        REQUIRE_EQ(p1.x(), p3.x() - p2.x());
        REQUIRE_EQ(p1.y(), p3.y() - p2.y());
    }
    SUBCASE("[coord] Les surcharges de =")
    {
        coord p1{2, 2};
        coord p3 = p1;
        REQUIRE_EQ(p3.x(), p1.x());
        REQUIRE_EQ(p3.y(), p1.y());
    }
}
