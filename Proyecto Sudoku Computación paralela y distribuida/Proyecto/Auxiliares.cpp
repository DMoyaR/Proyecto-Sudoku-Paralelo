#include "Auxiliares.h"

//Funciones para transformar direccion pegada a una valida
string dir(string nombre) {
    for (string::size_type i = 0; i < nombre.size(); i++) {

        if (nombre[i] == 92 && nombre[i - 1] != 92 && nombre[i + 1] != 92) {
            nombre.insert(i + 1, "\\");
            i++;
        }
    }
    return nombre;
}