#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <regex>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono; // Para simplificar el código

// Función para verificar si se puede colocar un número en la posición (row, col)
bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
    int n = board.size();
    int subgrid_size = sqrt(n);

    // Verificar fila
    for (int i = 0; i < n; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Verificar columna
    for (int i = 0; i < n; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Verificar subcuadro
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

// Función de retroceso para resolver el Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    int n = board.size();
    
    // Buscar una celda vacía
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] == 0) {
                // Intentar colocar números del 1 al n en la celda vacía
                for (int num = 1; num <= n; ++num) {
                    if (isSafe(board, row, col, num)) {
                        board[row][col] = num;

                        // Recursivamente intentar resolver el resto del tablero
                        if (solveSudoku(board)) {
                            return true;
                        }
                        // Si no se pudo resolver, revertir la asignación
                        board[row][col] = 0;
                    }
                }
                // Si no es posible colocar ningún número, retornar falso
                return false;
            }
        }
    }
    // Si no quedan celdas vacías, el Sudoku está resuelto
    return true;
}

// Función para leer el contenido del archivo JSON
vector<vector<int>> readJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    string line;
    string jsonContent;
    while (getline(file, line)) {
        jsonContent += line;
    }

    size_t start = jsonContent.find("[");
    size_t end = jsonContent.rfind("]");

    string boardContent = jsonContent.substr(start + 1, end - start - 1);

    vector<vector<int>> board;
    stringstream ss(boardContent);
    string row;

    while (getline(ss, row, ']')) {
        size_t pos = row.find("[");
        if (pos != string::npos) {
            row = row.substr(pos + 1);

            stringstream rowStream(row);
            string num;
            vector<int> currentRow;

            while (getline(rowStream, num, ',')) {
                currentRow.push_back(stoi(num));
            }

            if (!currentRow.empty()) {
                board.push_back(currentRow);
            }
        }
    }

    return board;
}

// Función para escribir el archivo JSON de salida
void writeJSON(const string& filename, const vector<vector<int>>& board) {
    ofstream file(filename);
    file << "{\n\"board\": [\n";
    for (size_t i = 0; i < board.size(); ++i) {
        file << "[";
        for (size_t j = 0; j < board[i].size(); ++j) {
            file << board[i][j];
            if (j != board[i].size() - 1) file << ", ";
        }
        file << "]";
        if (i != board.size() - 1) file << ",";
        file << "\n";
    }
    file << "]\n}\n";
}

// Función para imprimir el tablero
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    // Leer el tablero desde el archivo JSON
    vector<vector<int>> board = readJSON("C:\\Users\\franc\\OneDrive\\Escritorio\\Proyecto\\Proyecto\\sudoku.json");

    // Mostrar el tablero inicial
    cout << "Tablero inicial:\n";
    printBoard(board);

    // Medir el tiempo de ejecución
    auto start = high_resolution_clock::now();

    // Resolver el Sudoku
    if (solveSudoku(board)) {
        // Mostrar la solución
        cout << endl << "Sudoku resuelto secuencial:" << endl;
        for (const auto& row : board) {
            for (int num : row) {
                cout << num << " ";
            }
            cout << endl;
        }

        // Escribir el tablero resuelto en un archivo JSON
        writeJSON("sudoku_output_secuencial.json", board);
        //cout << "Sudoku resuelto y guardado en sudoku_output.json" << endl;
    } else {
        cout << "No se pudo resolver el Sudoku." << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << endl << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;

    return 0;
}