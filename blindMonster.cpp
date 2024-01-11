//
// Created by Daav on 18/11/2023.
//

#include <cstdlib>
#include <random>
#include <algorithm>
#include "blindMonster.h"
#include "display.h"
#include "castle.h"

blindMonster::blindMonster(int health, int strength, double hability, std::string type)
    : monster{health, strength, hability, type} {}

void blindMonster::move(castle &castle, std::shared_ptr<adventurer> &adventurer, std::shared_ptr<monster> &monster) {
    // Les 8 déplacements possibles
    int possibleX[] = {0, 0, -1, 1, -1, 1, -1, 1};
    int possibleY[] = {1, -1, 0, 0, 1, 1, -1, -1};

    // Création d'un ordre aléatoire des directions possibles
    vector<int> directions = {0, 1, 2, 3, 4, 5, 6, 7};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(directions.begin(), directions.end(), gen);

    // Essayer de se déplacer dans chaque direction jusqu'à trouver une case valide
    for(int i = 0; i < directions.size(); ++i) {
        int newX = position().x() + possibleX[directions[i]];
        int newY = position().y() + possibleY[directions[i]];

        // Vérifier si la nouvelle case est à l'intérieur des limites du château
        if(newX >= 0 && newY >= 0 && newX < castle.d_boxes.size() && newY < castle.d_boxes[0].size()) {
            // Vérifier si la nouvelle case est accessible et que le monstre peut y accéder
            if(castle.d_boxes[newX][newY].accessibility()) {
                // On vérifie ce qu'on a fait du monstre en essayant de le mettre dans la case et on le bouge si nécessaire
                int status = castle.d_boxes[newX][newY].putCharacter(monster);
                
                if(status == box::BX_MOVE_ON_ATTACK || status == box::BX_MOVE)
                {
                    castle.d_boxes[position().x()][position().y()].removeCharacter();
                    character::move(newX, newY);
                    break;
                }
            }
        }
    }
}

void blindMonster::show(display &d) const
{
    d.displayBlindMonster();
}
