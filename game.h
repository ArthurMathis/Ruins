#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>
#include "character.h"
#include "monster.h"
#include "castle.h"
#include <memory>
using std::vector;
using std::cin;
using std::cout;

#define MAIN_MENU "\
########################################################\n\
##             ------ CASTLE GAME ------              ##\n\
##              -------- MENU ---------               ##\n\
##                                                    ##\n\
##             (1) JOUER                              ##\n\
##             (2) CHARGER UN CHÂTEAU                 ##\n\
##             (3) ÉDITER LE CHÂTEAU                  ##\n\
##             (4) RÈGLES DU JEU                      ##\n\
##             (5) QUITTER                            ##\n\
##                                                    ##\n\
##                                                    ##\n\
########################################################\n\
"

#define RULES "\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
@                    ------ RÈGLES ------                    @\n\
@                                                            @\n\
@    Le jeu se deroule par tours. Durant chaque tour,        @\n\
@    vous vous deplacez en choisissant une direction         @\n\
@    si vous êtes sur un tas de pieces de monnaie,           @\n\
@    vous les ramassés. Aussi, chaque monstre se deplace,    @\n\
@    à chaque tour, si un monstre se deplace sur vous alors  @\n\
@    il vous attaque. Dans le cas contraire vous l'attaquer  @\n\
@    En vous deplacant sur lui.                              @\n\
@    À chaque attaque recu vos equipements perdent des       @\n\
@    points de solidité.                                     @\n\
@    Une piece d'or repare un point de solidite de l'epee    @\n\
@    ou de l'armure.                                         @\n\
@    Vous gagnez la partie lorsque vous sortez du chateau    @\n\
@    L'amulette.                                             @\n\
@                                                            @\n\
@                        BONNE CHANCE                        @\n\
@                                                            @\n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
"

#define LEGEND "\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
@            ------ LÉGENDE ------            @\n\
@                                             @\n\
@    W : Mur                                  @\n\
@    E : Case externe                         @\n\
@    C : Pièces (ex. C10 pour 10)             @\n\
@    Attention : Chaque case 'C' doit être    @\n\
@    doit être accompagnée d'un nombre        @\n\
@    représentant les pièces présentes        @\n\
@    sur la case.                             @\n\
@    A : Amulette                             @\n\
@    P : Aventurier (Un seul obligatoire)     @\n\
@    M : Monstre                              @\n\
@    B : Monstre aveugle                      @\n\
@                                             @\n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\
"

#define PLAYER_MENU "\
(1): ↑ (2): ↓ (3): → (4): ← (5): ↖ (6): ↗ (7): ↙ (8): ↘ \n\
"

class game {
public:
    /**
      * @brief Constructeur par défaut de la classe game.
      */
    game();

    /**
     * @brief Méthode pour afficher le menu principal et obtenir le choix de l'utilisateur.
     * @return Le choix de l'utilisateur.
     */
    int mainChoice() const;

    /**
     * @brief Méthode pour afficher les informations sur les monstres proches.
     */
    void monsterInfo();

    /**
     * @brief Méthode pour afficher le château et les informations des personnages.
     */
    void showCastle();

    /**
     * @brief Méthode pour obtenir le choix du joueur pendant le jeu.
     * @return Le choix du joueur.
     */
    int gameChoice() const;

    /**
     * @brief Méthode pour déplacer les monstres.
     */
    void moveMonsters();

    /**
     * @brief Méthode pour mettre à jour la liste des monstres (supprimer les monstres morts).
     */
    void updateMonsters();

    /**
     * @brief Méthode pour obtenir le choix de déplacement de l'aventurier.
     * @return Le choix de déplacement de l'aventurier.
     */
    int moveChoiceAdv() const;

    /**
     * @brief Méthode pour déplacer l'aventurier.
     */
    void moveAdventurer();

    /**
     * @brief Méthode pour réparer l'épée ou l'armure de l'aventurier.
     */
    void repairSwordOrArmor();

    /**
     * @brief Méthode pour quitter le jeu.
     */
    void close();

    /**
     * @brief Méthode pour gérer les actions du joueur pendant le jeu.
     */
    void gameMenu();

    /**
     * @brief Méthode pour afficher l'écran de fin de jeu.
     * @param res Le résultat du jeu (victoire ou défaite).
     */
    void end(bool res);

    /**
     * @brief Méthode principale du jeu, gérant les tours du joueur.
     */
    void loop();

    /**
     * @brief Méthode pour charger une carte depuis un fichier.
     */
    void loadMap();

    /**
     * @brief Méthode pour éditer le château.
     */
    void edit();

    /**
     * @brief Méthode pour afficher les règles du jeu.
     */
    void rules();

    /**
     * @brief Méthode pour démarrer le jeu en fonction du choix de l'utilisateur.
     */
    void start();
private:
    /// Pointeur partagé vers l'objet aventurier.
    std::shared_ptr<adventurer> d_adventurer;
    /// Vecteur de pointeurs partagés vers les objets monstre.
    vector<std::shared_ptr<monster>> d_monsters;
    /// Objet de la classe display.
    displayConsole d;
    /// Objet de la classe castle représentant le château du jeu.
    castle d_castle;
    /// Coordonnées de l'entrée du château.
    coord d_entrance;
};


#endif //__GAME_H__