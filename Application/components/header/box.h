#ifndef __CASE_H__
#define __CASE_H__

#include <iostream>
#include "character.h"

class box {
public:
    /**
    * @brief Construct a new box object
    * 
    * @param type : the type of the box
    * @param coins : the number of coins in the current box
    * @param c : the pointer to the character in the box
    */
    box(const std::string &type, int coins = 0, character* c = nullptr);

    /**
     * The list of the diffrents types of boxs
     */
     static const std::string BX_WALL;
     static const std::string BX_EMPTY;
     static const std::string BX_COINS;
     static const std::string BX_EXTERN;
     static const std::string BX_AMULET;

    /**
     * @brief the type of the box
     * 
     * @return std::string 
     */
    std::string type() const;


    /**
     * @brief the accessibility of the box
     * 
     * @return true 
     * @return false 
     */
    bool accessibility() const;

    /*
     * @brief return the number of coins present in the box
     * 
     * @return int 
     */
    int coins() const;

    /**
     * @brief Put a character(adventurer, monster, blindMonster, etc..) in the box
     * 
     * @param c : the character(adventurer, monster, blindMonster, etc..)
     */
    void putCharacter(character *c);

    /**
     * @brief remove character from the current box
     * 
     */
    void removeCharacter();

    /**
     * @brief remove coins from the current box
     * 
     */
    void removeCoin();

    /**
     * @brief remove amulet from the current box
     * 
     */
    void removeAmulet();

private:
    character *d_character;
    std::string d_type;
    bool d_accessibility, d_amulet;
    int d_coins;

    void changeType(const std::string &type);

};


#endif //__CASE_H__
