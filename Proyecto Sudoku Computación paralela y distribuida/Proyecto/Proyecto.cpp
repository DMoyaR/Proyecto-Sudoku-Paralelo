// Proyecto.cpp: define el punto de entrada de la aplicación.
//
#include "Proyecto.h"
#include "JsonClass.h"
#include "SudokuClass.h"
#include "Auxiliares.h"

int main() {
    string nombreJson;
    string salidaJson;
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);

    cout << "Ingrese direccion del archivo a importar (ejemplo: C:\\Users\\carpeta\\archivo.json)" << endl << "direccion:";
    getline(cin, nombreJson);
    nombreJson = dir(nombreJson);

    // Leer el contenido del archivo JSON
    string json_content = json::leerJson(nombreJson);

    // Leer el tablero desde el JSON
    vector<vector<int>> board = json::readJSON(json_content);

    sudoku tablero(board);

    // Mostrar tamaño de la matriz
    int n = board.size();
    cout << endl << "Tamano de la matriz:"<< n <<"x"<< n << endl << endl;

    // Mostrar el tablero leido
    cout << endl << "Tablero de entrada leido desde JSON:" << endl;
    tablero.printBoard(board);

    auto start = high_resolution_clock::now();
    // Resolver el Sudoku
    if (tablero.solveSudokuParalelo(board)) {
        // Mostrar el tablero resuelto en consola
        cout << endl << "Tablero resuelto" << endl;
        tablero.printBoard(board);

        // Escribir el tablero resuelto en archivo JSON
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << endl << "Tiempo de ejecucion: " << duration.count() << " ms" << endl;
        cout << endl << "Ingrese direccion para exportar el archivo sudoku_output.json (ejemplo: C:\\Users\\carpeta):";
        getline(cin, salidaJson);
        salidaJson = dir(salidaJson);
        salidaJson = salidaJson + "\\\\sudoku_output.json";

        json::writeJSON(salidaJson, board);
        cout << "Sudoku resuelto y guardado en sudoku_output.json" << endl;

    }
    else {
        cout << "No se pudo resolver el Sudoku." << endl;
    }

    return 0;
}


