#include "../header/box.h"
#include <stdexcept>

const std::string box::BX_WALL = "wall";
const std::string box::BX_ACCESSIBLE = "accessible";
// const std::string box::BX_COINS = "coins";
const std::string box::BX_EXTERN = "extern";
// const std::string box::BX_AMULET = "amulet";

box::box(const std::string &type, int coins, bool amulet, character *c) : d_type{type}, d_coins{0}, d_amulet{false}
{
    if(!isValidType())
        throw std::invalid_argument("InvalidType: type must in defined must be BX_WALL, BX_ACCESSIBLE or BX_EXTERN");

    if(d_type == box::BX_WALL || d_type == box::BX_EXTERN)
        d_accessibility = false;
    else
    {
        d_accessibility = true;

        if(coins == 0)
            d_amulet = amulet;
        if(!amulet)
            d_coins = coins;

        d_character = c;
    }
}

std::string box::type() const {
    return d_type;
}

bool box::accessibility() const {
    return d_accessibility;
}

bool box::hasAmulet() const {
    return d_amulet;
}

bool box::hasCoins() const {
    return d_coins > 0;
}

int box::coins() const {
    return d_coins;
}

character* box::getCharacter() const {
    return d_character;
}

bool box::putCharacter(character *c) {
    // attack the character in the box
    if(d_character)
    {
        c->attack(*d_character);
        // change the current character to the new one if it's dead
        if(d_character->isDead())
            d_character = c;
        else
            return false;
    }
    else
        d_character = c;
    return true;
}

void box::removeCharacter() {
    d_character = nullptr;
}

void box::removeCoins() {
    d_coins = 0;
}

void box::removeAmulet() {
    d_amulet = false;
}


bool box::isValidType() const
{
    std::string types[]= {
        box::BX_WALL,
        box::BX_ACCESSIBLE,
        // box::BX_COINS,
        box::BX_EXTERN,
        // box::BX_AMULET,
    };

    for(auto type: types)
    {
        if (type == d_type)
            return true;
    }
    return false;
}