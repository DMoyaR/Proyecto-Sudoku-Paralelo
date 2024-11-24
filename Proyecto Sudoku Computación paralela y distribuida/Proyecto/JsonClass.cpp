#include "JsonClass.h"

string json::leerJson(const string& nombreJson) {
    ifstream file(nombreJson);

    if (!file.is_open()) {
        cerr << endl << "Error al abrir el archivo JSON: " << nombreJson << endl << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

vector<vector<int>> json::readJSON(const string& content) {
    vector<vector<int>> board;

    // Captura los numero entre los corchetes []
    regex pattern(R"(\[(\d+(?:,\s*\d+)*)\])");
    smatch match;
    string data = content;

    // Se usa regex para encontrar todas las filas dentro de los corchetes
    auto begin = std::sregex_iterator(data.begin(), data.end(), pattern);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        string rowStr = it->str(1); // Se extrae la parte entre corchetes
        vector<int> row;

        // Procesar cada numero dentro de la fila
        stringstream ss(rowStr);
        string numStr;
        while (getline(ss, numStr, ',')) {
            try {
                row.push_back(stoi(numStr));  // Convertir a entero
            }
            catch (const invalid_argument& e) {
                cout << "Error al convertir el número: " << numStr << endl;
            }
        }

        board.push_back(row); // Agregar la fila al tablero
    }

    return board;
}

// Funcion para escribir el archivo JSON de salida
void json::writeJSON(const string& filename, const vector<vector<int>>& board) {
    ofstream file(filename);
    file << "{\n\t\t\"board\": [\n";
    for (size_t i = 0; i < board.size(); ++i) {
        file << "\t\t\t\t[";
        for (size_t j = 0; j < board[i].size(); ++j) {
            file << board[i][j];
            if (j != board[i].size() - 1) file << ", ";
        }
        file << "]";
        if (i != board.size() - 1) file << ",";
        file << "\n";
    }
    file << "\t\t]\n}\n";
    file.close();
}