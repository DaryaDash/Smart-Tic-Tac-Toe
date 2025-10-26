#pragma once

#include "GUI.hpp"

#include "Board.hpp"

class Game {
public:
    void run();
    
private:
    GUI gui;
    bool isRun;
    Board board;
    Board::Cell plr = Board::Cell::X;
    Board::Cell curr(Board::Cell who);
    void restart();
    void ticTackToe();
    void menu();
    
    
};

