#pragma once

#include "Proyecto.h"

class sudoku {
private: // atributos
    vector<vector<int>> board;
public: // métodos
    sudoku(const vector<vector<int>>& initialBoard) : board(initialBoard) {} // constructor
    bool solveSudokuSecuencial(vector<vector<int>>& board);
    bool solveSudokuParalelo(vector<vector<int>>& board);
    bool isSafe(const vector<vector<int>>& board, int row, int col, int num);
    void printBoard(const vector<vector<int>>& board);
};

