#pragma once

#include "Proyecto.h" 

class json {
public:
    static string leerJson(const string& nombreJson);
    static vector<vector<int>> readJSON(const string& content);
    static void writeJSON(const string& filename, const vector<vector<int>>& board);
};
