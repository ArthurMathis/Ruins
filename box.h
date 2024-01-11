#ifndef __CASE_H__
#define __CASE_H__

#include <iostream>
#include "character.h"
#include <memory>

class box {
public:
    /**
     * @brief Liste des différents types de cases.
     */
    static const std::string BX_WALL;
    static const std::string BX_ACCESSIBLE;
    static const std::string BX_EXTERN;

    /**
    * @brief Constantes pour indiquer le statut d'une opération de déplacement de personnage.
    */
    static constexpr int BX_AVOID  = 0;
    static constexpr int BX_MOVE   = 1;
    static constexpr int BX_ATTACK = 2;
    static constexpr int BX_MOVE_ON_ATTACK = 3;

    /**
     * @brief Constructeur d'une nouvelle case.
     *
     * @param type - Le type de la case (BX_WALL, BX_ACCESSIBLE, BX_EXTERN).
     * @param coins - Le nombre de pièces dans la case (par défaut 0).
     * @param amulet - La présence d'une amulette dans la case (par défaut false).
     * @param c - Le personnage présent dans la case (par défaut nullptr).
     */
    box(const std::string &type, int coins = 0, bool amulet = false, std::shared_ptr<character> c = nullptr);

    /**
     * @brief Renvoie le type de la case.
     *
     * @return Le type de la case.
     */
    std::string type() const;


    /**
     * @brief Renvoie la disponibilité de la case.
     *
     * @return true si la case est accessible, false sinon.
     */
    bool accessibility() const;

    /**
     * @brief Vérifie si la case contient une amulette.
     *
     * @return true si la case contient une amulette, false sinon.
     */
    bool hasAmulet() const;

    /**
     * @brief Vérifie si la case contient des pièces.
     *
     * @return true si la case contient des pièces, false sinon.
     */
    bool hasCoins() const;

    /**
     * @brief Renvoie le nombre de pièces dans la case.
     *
     * @return int - Le nombre de pièces.
     */
    int coins() const;

    /**
     * @brief Renvoie le personnage présent dans la case.
     *
     * @return std::shared_ptr<character> - Le personnage.
     */
    std::shared_ptr<character> getCharacter() const;

    /**
     * @brief Place un personnage dans la case.
     *
     * @param c - Le personnage à placer dans la case.
     * @return BX_MOVE si le personnage a été correctement déplacé dans la case.
     *         BX_MOVE_ON_ATTACK si le personnage a été déplacé après son attaque.
     *         BX_AVOID s'il n'a pas pu être déplacé et BX_ATTACK si le personnage a attaqué.
     */
    int putCharacter(std::shared_ptr<character> c);

    /**
     * @brief Supprime le personnage de la case.
     */
    void removeCharacter();

    /**
     * @brief Supprime les pièces de la case.
     */
    void removeCoins();

    /**
     * @brief Supprime l'amulette de la case.
     */
    void removeAmulet();

    /**
     * @brief Vérifie si le type de la case est valide.
     *
     * @return true si le type est valide, false sinon.
     */
    bool isValidType() const;

    /**
     * @brief Affiche le contenu de la case dans l'interface graphique.
     *
     * @param d - L'objet de type display responsable de l'affichage.
     */
    void show(display &d) const;
private:
    /// Le pointeur vers le personnage présent dans la case.
    std::shared_ptr<character> d_character;
    /// Le type de la case (BX_WALL, BX_ACCESSIBLE, BX_EXTERN).
    std::string d_type;
    /// L'accessibilité de la case (true si la case est accessible, false sinon).
    bool d_accessibility;
    /// La présence d'une amulette dans la case (true si présente, false sinon).
    bool d_amulet;
    /// Le nombre de pièces dans la case.
    int d_coins;
};


#endif //__CASE_H__
