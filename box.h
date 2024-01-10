#ifndef __CASE_H__
#define __CASE_H__

#include <iostream>
#include "character.h"
#include <memory>

class box {
public:
    /**
    * @brief Construct a new box object
    * 
    * @param type : the type of the box
    * @param coins : the number of coins in the current box
    * @param c : the pointer to the character in the box
    */
    box(const std::string &type, int coins = 0, bool amulet = false, std::shared_ptr<character> c = nullptr);

    /**
     * The list of the diffrents types of boxs
     */
     static const std::string BX_WALL;
     static const std::string BX_ACCESSIBLE;
    //  static const std::string BX_COINS;
     static const std::string BX_EXTERN;
    //  static const std::string BX_AMULET;

    static constexpr int BX_AVOID  = 0;
    static constexpr int BX_MOVE   = 1;
    static constexpr int BX_ATTACK = 2;
    static constexpr int BX_MOVE_ON_ATTACK = 3;


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

    /**
     * @brief Check if the box has an amulet
     * 
     * @return true 
     * @return false 
     */
    bool hasAmulet() const;

    /**
     * @brief Check if the box has an coins
     * 
     * @return true 
     * @return false 
     */
    bool hasCoins() const;

    /*
     * @brief return the number of coins present in the box
     * 
     * @return int 
     */
    int coins() const;

    /*
     * @brief return the number of coins present in the box
     *
     * @return int
     */
    std::shared_ptr<character> getCharacter() const;

    /**
     * @brief Put a character(adventurer, monster, blindMonster, etc..) in the box
     * 
     * @param c : the character(adventurer, monster, blindMonster, etc..)
     * @return BX_MOVE if the character has been correctly moved to the case
     * BX_AVOID if not and BX_ATTACK if the character made an attack
     */
    int putCharacter(std::shared_ptr<character> c);

    /**
     * @brief remove character from the current box
     * 
     */
    void removeCharacter();

    /**
     * @brief remove coins from the current box
     * 
     */
    void removeCoins();

    /**
     * @brief remove amulet from the current box
     * 
     */
    void removeAmulet();

    /**
     * @brief Check if the box type is valid
     * 
     * @return true 
     * @return false 
     */
    bool isValidType() const;

    void show(display &d) const;
private:
    std::shared_ptr<character> d_character;
    std::string d_type;
    bool d_accessibility, d_amulet;
    int d_coins;
};


#endif //__CASE_H__
