#include "game.h"
#include <stdlib.h>

/**
 * @brief Clear console
 * 
 */
void clrscr()
{
    #ifdef _WIN32
	    system("cls");
	#else
	    system("clear");
	#endif
}

void askcontinue()
{
    char choice;
    cout << "OK (c) >> ";
    cin >> choice;
}

game::game() : d_adventurer{std::make_shared<adventurer>()}, d_monsters{} {
    d_castle.init(d_adventurer, d_monsters);
    d_entrance = d_adventurer->position();
}

int game::mainChoice() const
{
    clrscr();
    int choice {-1};
    do {
        cout << MAIN_MENU;
        cout << ">> ";
        cin >> choice;
    } while(choice < 1 || choice > 5);
    return choice;
}

void game::start() {
    int d = 0;
    do {
        d = mainChoice();
        switch (d) {
            case 1 : loop();
                break;
            case 2 : loadMap();
                break;
            case 3 : edit();
                break;
            case 4 : rules();
                break;
            case 5 : close();
                break;
        }
        cout << d;
        d = 0;
    } while(d != 5);
}

int game::gameChoice() const {
    int choice {-1};
    do {
        cout << "(1) VOUS DÉPLACER \n";
        cout << "(2) RÉPARER VOTRE ARMURE OU VOTRE ÉPÉE \n";
        cout << "(3) QUITTER (vous perderez votre avancement) \n";
        cout << "Votre choix : ";
        cin >> choice;
    } while(choice < 1 || choice > 3);
    return choice;
}

void game::gameMenu() {
    int d = gameChoice();
    switch (d) {
        case 1 : moveAdventurer();
            break;
        case 2 : repairSwordOrArmor();
            break;
        case 3 : close();
            break;
    }
}

// !(dead || (amulet && position))
// !dead
void game::loop()
{
    bool result;
    while(!d_adventurer->isDead() && !(d_adventurer->amulet() && d_adventurer->position() == d_entrance)) {
        showCastle();
        gameMenu();
    }
    if(d_adventurer->amulet() && d_adventurer->position() == d_entrance)
        result = true;
    else
        result = false;
    end(result);
}

int game::moveChoiceAdv() const
{
    int choice {-1};
    do {
        cout << PLAYER_MENU;
        cout << ">> ";
        cin >> choice;
    } while(choice < 0 || choice > 8);
    return choice;
}

void game::moveAdventurer() {
    int moveA;

    do {
        moveA = moveChoiceAdv();

        int lig = d_adventurer->position().x();
        int col = d_adventurer->position().y();

        switch(moveA) {
            case 1: lig -= 1; break;
            case 2: lig += 1; break;
            case 3: col += 1; break;
            case 4: col -= 1; break;
            case 5: col -= 1; lig -= 1; break;
            case 6: col += 1; lig -= 1; break;
            case 7: col -= 1; lig += 1; break;
            case 8: col += 1; lig += 1; break;
        }

        if(lig >= 0 && col >= 0 && lig < d_castle.d_boxes.size() && col < d_castle.d_boxes[0].size()) {
            if(d_castle.d_boxes[lig][col].accessibility())
            {
                int status = d_castle.d_boxes[lig][col].putCharacter(d_adventurer);

                if(status == box::BX_AVOID)
                    cout << "Déplacement impossible" << std::endl;
                else if(status == box::BX_ATTACK)
                {
                    cout << "Vous avez attaqué un monstre" << std::endl;
                    askcontinue();
                    break;
                }
                else
                {
                    if(status == box::BX_MOVE_ON_ATTACK)
                    {
                        cout << "Vous avez tué un monstre" << std::endl;
                        askcontinue();
                    }
                    d_castle.d_boxes[d_adventurer->position().x()][d_adventurer->position().y()].removeCharacter();
                    d_adventurer->move(lig, col);
                    updateMonsters();
                    moveMonsters();
                    break;
                }
            }
            else
            cout << "Déplacement impossible" << std::endl;
        }
    } while(moveA > 0 && moveA <= 8);
}

void game::repairSwordOrArmor() {
    int coinAmount;
    if(d_adventurer->coins())
    {
        do {
            cout << "Combien de pièces souhaitez-vous utiliser pour réparer (pour l'épée ou l'armure) ? ";
            cin >> coinAmount;

            if(coinAmount <= 0 || coinAmount > d_adventurer->coins()) {
                cout << "Nombre de pièces invalide. Veuillez saisir un nombre positif et inférieur ou égal à votre solde de pièces." << std::endl;
            }
        } while(coinAmount <= 0 || coinAmount > d_adventurer->coins());

        int choice;
        do {
            cout << "Que voulez-vous réparer ?" << std::endl;
            cout << "(1) L'épée" << std::endl;
            cout << "(2) L'armure" << std::endl;
            cout << "Votre choix : ";
            cin >> choice;
        } while(choice != 1 && choice != 2);

        if(choice == 1) {
            d_adventurer->repairSword(coinAmount);
            cout << "L'épée a bien été réparée.";
        } else {
            d_adventurer->repairArmor(coinAmount);
            cout << "L'armure a bien été réparée.";
        }
    }
    else
        cout << "Vous n'avez pas suffisamment de piece" << std::endl;

    askcontinue();
}

// Delete the dead monsters
void game::updateMonsters()
{
    int i = 0;
    while(i < d_monsters.size())
    {
        if(d_monsters[i]->isDead())
            d_monsters.erase(d_monsters.begin() + i);
        else
            i++;
    }
}


void game::moveMonsters() {
    for(auto &m : d_monsters)
    {
        m->move(d_castle, d_adventurer, m);
    }
}

void game::end(bool res) {
    int choice;
    bool validChoice = false;

    clrscr();
    d_adventurer->info();

    d_castle.init(d_adventurer, d_monsters);

    while(!validChoice)
    {
        // Afficher le menu principal avec le résultat
        std::cout << "#######################################################\n"
                     "##             ------ CASTLE GAME ------             ##\n"
                     "##                                                   ##\n";

        if(res) {
            std::cout << "##       Félicitations ! Vous avez gagné ! :)        ##\n";
        } else {
            std::cout << "##            Dommage, vous avez perdu. :(           ##\n";
        }

        std::cout << "##                                                   ##\n"
                     "##            (1) Retour au Menu Principal           ##\n"
                     "##            (2) Quitter                            ##\n"
                     "##                                                   ##\n"
                     "#######################################################\n";

        // Demander à l'utilisateur de choisir une option
        std::cout << "Choisissez une option : ";
        std::cin >> choice;

        // Traiter la sélection de l'utilisateur
        switch(choice) {
            case 1:
                validChoice = true;  // La sélection est valide, sortir de la boucle
                start();  // Appeler la méthode play pour relancer le jeu
                break;
            case 2:
                close();  // Quitter la boucle et la fonction
                return;
            default:
                std::cout << "Choix invalide. Veuillez sélectionner une option valide." << std::endl;
                break;
        }
    }
}

void game::rules() {
    clrscr();
    // cout << ":\n";
    // cout << "- l'utilisateur deplace l'aventurier; si l'aventurier est sur un tas de pieces de monnaie, il les ramasse.\n";
    // cout << "- chaque monstre se deplace; si un monstre se deplace sur l'aventurier alors il l'attaque.\n";
    // cout << "- le joueur peut choisir de reparer son equipement avec des pieces d'or.\n";
    // cout << "  - Une piece d'or repare un point de solidite de l'epee ou de l'armure.\n";
    // cout << "  - L'epee perd un point de solidite a chaque attaque.\n";
    // cout << "  - L'armure perd des points de solidite lors d'attaques de monstres.\n";
    // cout << "  - Les points repares sont pris a partir des pieces d'or dans la bourse de l'aventurier.\n";
    // cout << "- le jeu se termine soit quand l'aventurier est mort, soit quand il est a la sortie du chateau avec l'amulette.\n";
    cout << RULES;
    askcontinue();

}

void game::edit() {
    clrscr();
    cout << "Pour éditer le château, veuillez modifier le fichier defaultCastle.txt ou créer un nouveau fichier .txt en utilisant la légende suivante :" << std::endl << std::endl;
    cout << LEGEND;
    cout << std::endl;
    askcontinue();

}

void game::monsterInfo() {
    bool monsterNear = false;
    int index = 0;

    for(const auto& m : d_monsters) {
        if(m->isNearInfo(d_adventurer)) {
            cout << "----- INFO MONSTRES -----" << std::endl;
            m->info();
            cout << "-------------------------" << std::endl;
            monsterNear = true;
            break;
        }
        index++;
    }

    if(monsterNear) {
        // cout << "----- INFO MONSTRES -----" << std::endl;

        for (int i = index + 1; i < d_monsters.size(); i++) {
            if(d_monsters[i]->isNearInfo(d_adventurer)) {
                d_monsters[i]->info();
                cout << "-------------------------" << std::endl;
            }
        }
    }
}

void game::showCastle() {
    clrscr();
    int width = d_castle.d_boxes[0].size();

    for(int i = 0; i < width; ++i)
        cout << "+---";
    cout << "+ ";

    for (const auto& row : d_castle.d_boxes) {
        cout << std::endl;
        cout << "+";
        for (const auto& box : row) {
            cout << "  ";
            box.show(d);
            cout << " ";
        }
        cout << " +";
    }
    cout << std::endl << " ";
    for(int i = 0; i < width; ++i)
        cout << "+---";
    cout << '+' << std::endl;
    d_adventurer->info();
    monsterInfo();
}

void game::loadMap() {
    clrscr();
    string mapName;
    cout << "Entrez le nom de la carte à charger (par exemple, 'map2.txt') : ";
    cin >> mapName;
    bool loaded = d_castle.load(mapName, d_adventurer, d_monsters);
    if(loaded) {
        d_entrance = d_adventurer->position();
        cout << "La carte " << mapName << " a bien été chargée !" << std::endl;
    }

    askcontinue();

}

void game::close()
{
    cout << "À bientôt !" << std::endl;
    std::exit(0);
}
