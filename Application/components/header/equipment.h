#ifndef __equipment_H__
#define __equipment_H__

class equipment {
public:
    /**
       * @brief Construct a new object object
       * @param solidity le point de solidité de l'équipement crée
       */
    equipment(int solidity);
    /**
        * @brief Renvoie le solidité de l'équipement
        * @return int
        */
    int solidity() const;
    /**
        * @brief Reduit le point de solidité d'un équipement
        * @pre nb > 0
        * @param nb nombre de reduction
        */
    void reduce(int nb);
    /**
        * @brief Augmente le point de solidité d'un équipement
        * @pre nb > 0
        * @param nb nombre d'augmentation
        */
    void increase(int nb);
private:
    /// point de solidité
    int d_solidity;
};

#endif