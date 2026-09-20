#include <iostream>
#include "tablero.h"

int main()
{
    int filas = 5, columnas = 5;
    int bytesReservados = 0;

    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    std::cout << "Tablero creado: " << filas << "x" << columnas
              << " (" << bytesReservados << " bytes reservados)" << std::endl;

    liberarTablero(tablero);

    return 0;
}
