#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

class equipment {
public:
    /**
     * @brief Constructeur de la classe equipment.
     *
     * @param solidity Le point de solidité de l'équipement créé.
     */
    equipment(int solidity);

    /**
     * @brief Renvoie le point de solidité de l'équipement.
     *
     * @return int La solidité de l'équipement.
     */
    int solidity() const;

    /**
     * @brief Réduit le point de solidité de l'équipement.
     *
     * @pre nb > 0
     * @param nb Le nombre de réduction.
     */
    void reduce(int nb);

    /**
     * @brief Augmente le point de solidité de l'équipement.
     *
     * @pre nb > 0
     * @param nb Le nombre d'augmentation.
     */
    void increase(int nb);

    /**
     * @brief Modifie la solidité de l'équipement avec une nouvelle valeur.
     *
     * @param value La nouvelle valeur de solidité.
     */
    void setSolidity(int value);

private:
    /// Le point de solidité de l'équipement.
    int d_solidity;
};

#endif // __EQUIPMENT_H__