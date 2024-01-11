//
// Created by Daav on 19/12/2023.
//

#ifndef APPLICATION_CASTLE_H
#define APPLICATION_CASTLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "box.h"
#include "adventurer.h"
#include "monster.h"
#include <memory>
using std::vector;
using std::string;

class castle {
public:
    /**
     * @brief Constructeur par défaut de la classe castle
     */
    castle() = default;

    /**
      * @brief Méthode qui convertit le type de la case en code
      * @param box La case dont le type doit être converti en code
      * @return Le code correspondant au type de la case
      */
    string typeCode(const box &box) const;

    /**
     * @brief Méthode qui onvertit le code en type de case
     * @param type Le code du type de la case à convertir
     * @return La case correspondant au type du code
     */
    box boxFromType(const string &type, std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters, int i, int j) const;

    /**
     * @brief Méthode qui initialise le château
     */
    void init(std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters);

    /**
     * @brief Méthode qui sauvegarde le terrain dans un fichier txt
     * @param filename Le nom du fichier de sauvegarde
     */
    void save(const std::string &filename);

    /**
     * @brief Méthode qui charge le terrain à partir d'un fichier txt
     * @param filename Le nom du fichier à charger
     */
    bool load(const std::string &filename, std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters);

    /// Grille représentant le château
    vector<vector<box>> d_boxes;
};


#endif //APPLICATION_CASTLE_H
