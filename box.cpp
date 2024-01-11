#include "box.h"
#include "adventurer.h"
#include <stdexcept>

const std::string box::BX_WALL = "wall";
const std::string box::BX_ACCESSIBLE = "accessible";
const std::string box::BX_EXTERN = "extern";

box::box(const std::string &type, int coins, bool amulet, std::shared_ptr<character> c) : d_type{type}, d_coins{0}, d_amulet{false}
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

std::shared_ptr<character> box::getCharacter() const {
    return d_character;
}

int box::putCharacter(std::shared_ptr<character> c) {
    int status = box::BX_AVOID;
    if(d_character) {
        // Check if the current character hasn't the same type
        if(d_character->type() != c->type())
        {
            // Attack the character in the box
            c->attack(*d_character);
            if(d_character->isDead())
                status = box::BX_MOVE_ON_ATTACK;
            else
                status = box::BX_ATTACK;
        }
        // If both characters are the same, do not allow insertion
        // do nothing
    }
    else
        status = box::BX_MOVE;

    if(status == box::BX_MOVE_ON_ATTACK || status == box::BX_MOVE)
    {
        d_character = c;
        // Check if the replaced character is an adventurer, if yes, pick up coins or amulet if present
        auto adventurerPtr = std::dynamic_pointer_cast<adventurer>(c);
        if(adventurerPtr) {
            if(hasCoins()) {
                adventurerPtr->addCoins(d_coins);
                removeCoins();
            }
            if(hasAmulet()) {
                adventurerPtr->takeAmulet();
                removeAmulet();
            }
        }
    }

    return status;
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
        box::BX_EXTERN,
    };

    for(auto type: types)
    {
        if (type == d_type)
            return true;
    }
    return false;
}

void box::show(display &d) const {
    if (d_type == BX_WALL) {
        d.displayWall();
    } else if (d_type == BX_EXTERN) {
        d.displayExternCase();
    } else if (d_type == BX_ACCESSIBLE) {
        if (d_amulet) {
            d.displayAmulet();
        } else if (d_character != nullptr) {
            // Affichage du personnage selon son type
            d_character->show(d);
        } else if (d_coins > 0){
            d.displayCoin();
        } else {
            // Case vide
            d.displayEmptyCase();
        }
    } else {
        d.displayEmptyCase();
    }
}

