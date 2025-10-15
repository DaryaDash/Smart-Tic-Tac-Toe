#pragma once

#include <array>
#include <iostream>
#include <algorithm>

class Board {
    public:
        enum class Cell { Empty = '_', X = 'X', O = 'O' };

    private:
        static constexpr int N = 3;
        std::array<Cell, N * N> cells{};
        static int idx(int i, int j) { return i * N + j; }

        int winner(Cell c){
            if (c == Cell::O) return -1;
            if (c == Cell::X) return 1;
            if (c == Cell::Empty) return 0;
        

            return -2;
        }
public:
        Board() { cells.fill(Cell::Empty); }

        void clear(){ cells.fill(Cell::Empty); }
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
                     if (cells[idx(i,0)] == cells[idx(i,1)] &&(cells[idx(i,1)] == cells[idx(i,2)]) && cells[idx(i,0)] != Cell::Empty) return  winner(cells[idx(i,0)]);
                }
            for ( int j = 0; j <3; ++j ) {
                     if (cells[idx(0,j)] == cells[idx(1,j)] &&(cells[idx(1,j)] == cells[idx(2,j)]) && cells[idx(0,j)] != Cell::Empty) return  winner(cells[idx(0,j)]);
                }
            if (cells[idx(0,0)] == cells[idx(1,1)] &&(cells[idx(1,1)] == cells[idx(2,2)]) && cells[idx(0,0)] != Cell::Empty ) return  winner(cells[idx(0,0)]);
            if (cells[idx(0,2)] == cells[idx(1,1)] &&(cells[idx(1,1)] == cells[idx(2,0)]) && cells[idx(1,1)] != Cell::Empty ) return  winner(cells[idx(0,2)]);
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

