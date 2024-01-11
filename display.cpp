#include "display.h"
#include<iostream>
#include <iomanip>

const std::string display::BLACK   = "\033[1;30m";
const std::string display::RED     = "\033[1;31m";
const std::string display::GREEN   = "\033[1;32m";
const std::string display::YELLOW  = "\033[1;33m";
const std::string display::PURPLE  = "\033[1;35m";
const std::string display::CYAN  = "\033[1;36m";
const std::string display::WHITE   = "\033[0;37m";

void display::displayAdventurer()
{
    std::cout << display::WHITE;
    std::cout << "P";
    std::cout << display::WHITE;
}

void display::displayMonster()
{
    std::cout << display::RED;
    std::cout << "M";
    std::cout << display::WHITE;
}

void display::displayBlindMonster()
{
    std::cout << display::PURPLE;
    std::cout << "W";
    std::cout << display::WHITE;
}

void display::displayAmulet() {
    std::cout << display::CYAN;
    std::cout << "A";
    std::cout << display::WHITE;
}

void display::displayWall()
{
    std::cout << display::BLACK;
    std::cout << "#";
    std::cout << display::WHITE;
}

void display::displayEmptyCase()
{
    std::cout << " ";
    std::cout << display::WHITE;
}

void display::displayExternCase()
{
    std::cout << display::GREEN;
    std::cout << "X";
    std::cout << display::WHITE;
}
void display::displayCoin()
{
    std::cout << display::YELLOW;
    std::cout << "O";
    std::cout << display::WHITE;
}


