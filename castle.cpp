//
// Created by Daav on 19/12/2023.
//

#include "castle.h"
#include "blindMonster.h"

string castle::typeCode(const box &box) const {
    string code;

    // Vérifie le type de la case
    if(box.type() == box::BX_WALL) {
        code = "W";
    } else if(box.type() == box::BX_EXTERN) {
        code = "E";
    } else if(box.type() == box::BX_ACCESSIBLE) {
        // Si c'est une case accessible, on vérifie son contenu pour déterminer le code
        if(box.hasCoins())
            // Si elle contient des pièces, le code est C suivi du nombre de pièces
            code = "C" + std::to_string(box.coins());
        else if(box.hasAmulet())
            code = "A";
        else if(box.getCharacter() == nullptr)
            code = "R";
        else if(box.getCharacter()->type() == character::CHAR_ADVENTURER)
            code = "P";
        else if(box.getCharacter()->type() == character::CHAR_MONSTER)
            code = "M";
        else if(box.getCharacter()->type() == character::CHAR_BLINDMONSTER)
            code = "B";
    }

    return code;
}

box castle::boxFromType(const string &type, std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters, int i, int j) const {
    int coins = 0; // Initialisation du nombre de pièces

    // Vérifie le type de case passé en paramètre et crée la case correspondante
    if(type == "W") {
        return box(box::BX_WALL);
    } else if(type == "E") {
        return box(box::BX_EXTERN);
    } else if(type[0] == 'C') {
        // Si le type commence par C, on extrait le nombre de pièces du code
        coins = stoi(type.substr(1));
        return box(box::BX_ACCESSIBLE, coins);
    } else if(type == "A") {
        return box(box::BX_ACCESSIBLE, 0, true);
    } else if(type == "R") {
        return box(box::BX_ACCESSIBLE);
    } else if(type == "P") {
        // Placement de l'aventurier
        adventurer->move(i,j);
        // Réinitialiser l'aventurier
        adventurer->reset();
        return box(box::BX_ACCESSIBLE, 0, false, adventurer);
    } else if(type == "M") {
        std::shared_ptr<monster> m = std::make_shared<monster>();
        // Placement du monstre
        m->character::move(i,j);
        // Réinitialiser le monstre
        m->reset();
        monsters.push_back(std::move(m));
        return box(box::BX_ACCESSIBLE, 0, false, monsters.back());
    } else if(type == "B") {
        std::shared_ptr<blindMonster> m = std::make_shared<blindMonster>();
        // Placement du monstre
        m->character::move(i,j);
        // Réinitialiser le monstre
        m->reset();
        monsters.push_back(std::move(m));
        return box(box::BX_ACCESSIBLE, 0, false, monsters.back());
    }
}

void castle::init(std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters) {
    // On charge la map de base
    load("./defaultCastle.txt", adventurer, monsters);
}

void castle::save(const string &filename) {
    std::ofstream file(filename);

    if(file) {
        // On parcourt chaque ligne de cases dans la grille du château
        for(const auto& row : d_boxes) {
            // On parcourt chaque case dans une ligne de la grille
            for(const auto& box : row)
                // On écrit le code correspondant au type de la boîte suivi d'un espace
                file << typeCode(box) << " ";
            // On va à la ligne après avoir écrit toutes les cases d'une ligne
            file << std::endl;
        }
        file.close();
    } else
        // Si le fichier n'a pas pu être ouvert, on envoie un message d'erreur
        std::cout << "Le fichier suivant n'a pas pu être sauvegardé : " << filename << std::endl;
}

bool castle::load(const string &filename, std::shared_ptr<adventurer> &adventurer, vector<std::shared_ptr<monster>> &monsters) {
    std::ifstream file(filename);

    if(file.is_open()) {
        d_boxes.clear();

        string line;
        int i = 0;
        // On parcourt chaque ligne du fichier représentant une ligne de cases dans la grille du château
        while(std::getline(file, line)) {
            int j = 0;
            // On crée un flux pour lire chaque code de case dans une ligne
            std::istringstream iss(line);
            // On stocke les cases d'une ligne de la grille
            vector<box> row;

            string code;
            // On parcourt chaque code de case dans une ligne de la grille
            while(iss >> code) {
                // On crée une case à partir du code et on l'ajoute à la ligne
                row.push_back(boxFromType(code, adventurer, monsters, i, j));
                j++;
            }

            // On ajoute la ligne complète à la grille du château
            d_boxes.push_back(row);
            i++;
        }

        file.close();
        return true;
    } else {
        // Si le fichier n'a pas pu être ouvert, on envoie un message d'erreur
        std::cout << "Le fichier suivant n'a pas pu être chargé : " << filename << std::endl;
        std::cout << "Veuillez vérifier le nom du fichier." << std::endl << std::endl;
        return false;
    }
}