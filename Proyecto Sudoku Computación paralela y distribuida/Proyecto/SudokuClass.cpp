#include "SudokuClass.h"

//funciones sudoku
bool sudoku::solveSudokuSecuencial(vector<vector<int>>& board) {
    int n = board.size();
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] == 0) { // si la casilla esta vacia
                for (int num = 1; num <= n; ++num) { // verifica si el numero ingresado respeta las reglas de sudoku
                    if (isSafe(board, row, col, num)) { // si el numero respeta las reglas lo ingresa a la casilla
                        board[row][col] = num;
                        if (solveSudokuSecuencial(board)) { // recursividad para el resto del tablero tablero
                            return true;
                        }
                        board[row][col] = 0; // eliminar el numero y retroceder
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Funcion principal para resolver el sudoku de manera paralela
bool sudoku::solveSudokuParalelo(vector<vector<int>>& board) {
    int n = board.size();
    int firstRow = -1, firstCol = -1;

    // Se busca la primera casilla vacia
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] == 0) {
                firstRow = row;
                firstCol = col;
                break;
            }
        }
        if (firstRow != -1) break;
    }

    if (firstRow == -1) return true; // Si no hay una casilla vacia esta listo
    bool foundSolution = false; // Indica el estado de la solucion aun no se encuentra

    // Se paraleliza la busque de las soluciones
#pragma omp parallel for shared(foundSolution, board)
    for (int num = 1; num <= n; ++num) {
        if (!foundSolution) { // Solo se trabaja si no se encontro una solucion
#pragma omp critical // Asegura que el acceso sea exclusivo
            {
                if (isSafe(board, firstRow, firstCol, num)) {
                    board[firstRow][firstCol] = num; // Se prueba el numnero
                    if (solveSudokuSecuencial(board)) {
                        foundSolution = true; // Indica que la solucion se encontro
                    }
                    if (!foundSolution) {
                        board[firstRow][firstCol] = 0; // Lo devuelve a 0 si no es solucion
                    }
                }
            }
        }
    }
    return foundSolution; // Devuelve true si ya se encontro una solucion
}

// Funcion para ver si se puede colocar un numero en una la casilla del tablero
bool sudoku::isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    int n = board.size();
    int subgrid_size = sqrt(n);

    // Para verificar la fila
    for (int i = 0; i < n; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Para verificar la columna
    for (int i = 0; i < n; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Para verificar la subcuadrado
    int startRow = row - row % subgrid_size;
    int startCol = col - col % subgrid_size;
    for (int i = 0; i < subgrid_size; ++i) {
        for (int j = 0; j < subgrid_size; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}


// Funcion para imprimir el tablero
void sudoku::printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}