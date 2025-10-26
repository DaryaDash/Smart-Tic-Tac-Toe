
#include <iostream>
#include "Game.hpp"
#include "Board.hpp"
#include "GUI.hpp"
#include <clocale>


int main() {
    setlocale(LC_ALL, "Russian");
    Game game;
    game.run();
    return 0;
}
