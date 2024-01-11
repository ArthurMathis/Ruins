#ifndef __SWORD_H__
#define __SWORD_H__

#include "equipment.h"

class sword: public equipment {
public:
    /**
      * @brief Constructeur d'une épée
      * @param solidity
      */
    sword(int solidity);
};

#endif