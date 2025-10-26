#pragma once

#include <array>
#include <iostream>
#include <algorithm>

struct Point{
            int x;
            int y;
            public:
            Point(){ this->x = 0; this-> y = 0; };
            Point(int x, int y): x(x), y(y) {} ;
     
        };


class Board {
    public:
        enum class Cell { Empty = '_', X = 'X', O = 'O' };
        int s = -2;
        std::array <Point, 3> win_cells{} ;

    private:
        static constexpr int N = 3;
        std::array<Cell, N * N> cells{};
        static int idx(int i, int j) { return i * N + j; }

        int winner(Cell c){
            if (c == Cell::O) this->s = -1;
            else if (c == Cell::X) this->s = 1;
            else if (c == Cell::Empty) this->s =  0;
            else this->s =  0;
            return this-> s;
        }


public:
    Board() { cells.fill(Cell::Empty); win_cells.fill(Point(-1, -1)); }
        
        
    void clear() {
        cells.fill(Cell::Empty); 
        win_cells.fill(Point(-1, -1));
       }
        Cell at(int i, int j) const { return cells[idx(i, j)]; }

        
        bool makeMove(int i, int j, Cell who) {
            if (at(i, j) == Cell::Empty) {
                cells[idx(i, j)] = who;
                return true;
            }
            return false;
        }

        int terminate(){
            for ( int i = 0; i <3; ++i ) {
                     if (cells[idx(i,0)] == cells[idx(i,1)] &&(cells[idx(i,1)] == cells[idx(i,2)]) && cells[idx(i,0)] != Cell::Empty) 
                     {  
                         this->win_cells = { Point(i, 0),Point(i, 1),Point(i, 2) };

                        return  winner(cells[idx(i,0)]);
                     }
                }
            for (int j = 0; j < 3; ++j) {
                if (cells[idx(0, j)] == cells[idx(1, j)] && (cells[idx(1, j)] == cells[idx(2, j)]) && cells[idx(0, j)] != Cell::Empty)
                {
                    this->win_cells= { Point(0, j), Point(1, j), Point(2, j) };
                    return  winner(cells[idx(0, j)]);
                }
            }
                if (cells[idx(0, 0)] == cells[idx(1, 1)] && (cells[idx(1, 1)] == cells[idx(2, 2)]) && cells[idx(0, 0)] != Cell::Empty) {
                    this->win_cells = { Point(0, 0), Point(1, 1), Point(2, 2) };
                    return  winner(cells[idx(0, 0)]);

                }
                if (cells[idx(0, 2)] == cells[idx(1, 1)] && (cells[idx(1, 1)] == cells[idx(2, 0)]) && cells[idx(1, 1)] != Cell::Empty)
                {
                    this->win_cells = { Point(0, 2), Point(1, 1), Point(2, 0) };
                    return  winner(cells[idx(0, 2)]);
                }
            auto it = std::find(cells.begin(), cells.end(), Cell::Empty);
            if (it == cells.end()) {
                return winner(Cell::Empty);

            }
            return -2; // game continues
        }

        void printBaord() const {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    std::cout << static_cast<char>(at(i, j)) << ' ';
                }
                std::cout << '\n';
            }
        }

        std::array<Cell, N * N>& getCells() { return cells; }
        const std::array<Cell, N * N>& getCells() const { return cells; }
};

