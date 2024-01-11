#include "displayConsole.h"
#include<iostream>
#include <iomanip>

const std::string displayConsole::BLACK   = "\033[1;30m";
const std::string displayConsole::RED     = "\033[1;31m";
const std::string displayConsole::GREEN   = "\033[1;32m";
const std::string displayConsole::YELLOW  = "\033[1;33m";
const std::string displayConsole::PURPLE  = "\033[1;35m";
const std::string displayConsole::CYAN  = "\033[1;36m";
const std::string displayConsole::WHITE   = "\033[0;37m";

void displayConsole::displayAdventurer() const
{
    std::cout << displayConsole::WHITE;
    std::cout << "P";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayMonster() const
{
    std::cout << displayConsole::RED;
    std::cout << "M";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayBlindMonster() const
{
    std::cout << displayConsole::PURPLE;
    std::cout << "W";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayAmulet() const {
    std::cout << displayConsole::CYAN;
    std::cout << "A";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayWall() const
{
    std::cout << displayConsole::BLACK;
    std::cout << "#";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayEmptyCase() const
{
    std::cout << " ";
    std::cout << displayConsole::WHITE;
}

void displayConsole::displayExternCase() const
{
    std::cout << displayConsole::GREEN;
    std::cout << "X";
    std::cout << displayConsole::WHITE;
}
void displayConsole::displayCoin() const
{
    std::cout << displayConsole::YELLOW;
    std::cout << "O";
    std::cout << displayConsole::WHITE;
}


