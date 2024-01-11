#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "equipment.h"

class armor: public equipment {
public:
    /**
     * @brief Constructeur d'une armure
     * @param solidity
     */
    armor(int solidity);
};

#endif