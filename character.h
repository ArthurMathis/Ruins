//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_CHARACTER_H
#define QUALITE_DE_PROG_CHARACTER_H

#include "coord.h"
#include "displayConsole.h"


class character {
public:
    /**
     * @brief Les différents types de personnage
     */
    static const std::string CHAR_ADVENTURER;
    static const std::string CHAR_MONSTER;
    static const std::string CHAR_BLINDMONSTER;

    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du personnage
     * @param strength Les points d'attaque du personnage
     * @param type Le type du personnage
     */
    character(int health, int strength, std::string type);
    /**
     * @brief Destructeur par défaut
     */
    virtual ~character() = default;

    /**
     * @brief Fonction renvoyant le nombre de points de vie
     * @return nombre de points de vie
     */
    int health() const;
    /**
      * @brief Fonction renvoyant le nombre de points de force
      * @return nombre de points de force
      */
    int strength() const;
    /**
     * @brief Fonction renvoyant la position
     * @return point de coordonnées
     */
    coord position() const;
    /**
     * @brief Fonction renvoyant le type du personnage
     * @return chaîne contenant le type du personnage
     */
     std::string type() const;

    /**
     * @brief Méthode permettant de déplacer un personnage
     * @param x - La nouvelle coordonnée x
     * @param y - La nouvelle coordonnée y
     */
    void move(int x, int y);

    /**
      * @brief Méthode virtuelle permettant à un personnage d'en attaquer un autre
      * @param c - Le personnage à attaquer
      */
    virtual void attack(character &c) = 0;
    /**
      * @brief Méthode virtuelle permettant de gérer la réception d'une attaque sur un personnage
      * @param attackStrength - Points de force de l'attaque
      */
    virtual void hasBeenAttacked(int attackStrength) = 0;
    /**
      * @brief Fonction permettant de vérifier si un personnage est mort
      * @return true si le personnage est mort, false s'il est vivant
      */
    bool isDead() const;
    /**
      * @brief Méthode permettant de gérer les dégâts infligés lors d'une attaque sur un personnage
      * @param[in] damage - Nombre de dégâts reçus
      */
    void getDamaged(int damage);

    /**
     * @brief Méthode virtuelle permettant d'afficher le personnage dans l'interface graphique.
     * @param d - L'objet de classe display pour l'affichage.
     */
    virtual void show(display &d) const = 0;

    /**
     * @brief Méthode virtuelle permettant de réinitialiser les paramètres du personnage.
     */
    virtual void reset() = 0;

    /**
     * @brief Méthode virtuelle affichant des informations spécifiques du personnage.
     */
    virtual void info() const = 0 ;
protected:
    /// Points de vie et points de force
    int d_health, d_strength;

    /**
      * @brief Méthode permettant de faire mourir un personnage
      */
    void die();
private:
    /// Coordonnées du character
    coord d_coord;
    /// Type du personnage
    std::string d_type;
};


#endif //QUALITE_DE_PROG_CHARACTER_H
