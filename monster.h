//
// Created by Daav on 18/11/2023.
//

#ifndef QUALITE_DE_PROG_MONSTER_H
#define QUALITE_DE_PROG_MONSTER_H

#include "character.h"
#include "adventurer.h"
#include "monster.h"
#include <memory>

class castle;
class monster : public character {
public :
    /// Constantes par défaut
    static constexpr int DEFAULT_HEALTH = 100;
    static constexpr int DEFAULT_STRENGTH = 10;
    static constexpr double DEFAULT_HABILITY = 90;

    /// Constantes de décision
    static constexpr int INFO_DISTANCE = 1;
    static constexpr int MOVE_TO_PLAYER_DISTANCE = 8;

    /**
     * @brief Constructeur par valeurs
     * @param health Les points de vie du monstre
     * @param strength Les points d'attaque du monstre
     * @param hability Son taux d'habilieté au coups critiques
     * @param type Type monstre voyant
     */
    monster(int health = DEFAULT_HEALTH, int strength = DEFAULT_STRENGTH, double hability = DEFAULT_HABILITY, std::string type = "monster");
    /**
      * @brief Destructeur par défaut
      */
    virtual ~monster() = default;

    /**
      * @brief Fonction renvoyant le pourcentage d'habilité
      * @return poucentage d'habilité
      */
    int hability() const;

    /**
      * @brief Réecriture de la méthode virtuelle permettant ainsi à un monstre d'attaquer un personnage
      * @param[in] c - Le personnage à attaquer
      */
    void attack(character &c) override;
    /**
      * @brief Réecriture de la méthode virtuelle permettant de gérer la réception d'une attaque par un monstre
      * @param attackStrengthPoints - Points de force de l'attaque
      */
    void hasBeenAttacked(int attackStrengthPoints) override;

    /**
      * @brief Méthode retournant si le joueur est suffisanement proche du monstre
      * @param adventurer l'aventurier
      * @return true si le joueur est proche (par rapport à MOVE_TO_PLAYER_DISTANCE)
      */
    bool isClose(std::shared_ptr<adventurer> &adventurer) const;
    /**
      * @brief Méthode retournant si le joueur est proche pour afficher les infos
      * @param adventurer l'aventurier
      * @return true si le joueur est proche (par rapport à INFO_DISTANCE)
      */
    bool isNearInfo(std::shared_ptr<adventurer> &adventurer) const;

    /**
     * @brief Méthode retournant dans quelle direction se situe le joueur
     * @param adventurer l'aventurier
     * @return Un entier représentant la direction
     */
    int direction(std::shared_ptr<adventurer> &adventurer) const;

    /**
     * @brief Calcule la nouvelle position du monstre voyant en fonction de la direction.
     *
     * @param direction Direction du déplacement.
     * @param newX Nouvelle coordonnée x.
     * @param newY Nouvelle coordonnée y.
     */
    void calculateNewPositionNotBlind(int direction, int &newX, int &newY);

    /**
     * @brief Méthode virtuelle permettant à un monstre de se déplacer en fonction de l'aventurier
     *
     * @param castle Château.
     * @param adventurer Aventurier.
     * @param monster Le monstre lui même.
     */
    virtual void move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster);

    /**
     * @brief Affiche le monstre dans l'interface graphique.
     * @param d - L'objet de type display responsable de l'affichage.
     */
    void show(display &d) const override;

    /**
      * @brief Réinitialise les attributs du monstre à leurs valeurs par défaut.
      */
    void reset() override;

    /**
     * @brief Affiche les informations sur le monstre.
     */
    void info() const override;
private:
    /// Pourcentage d'habilité du monstre
    double d_hability;
};

#endif //QUALITE_DE_PROG_MONSTER_H
