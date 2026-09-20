#include <iostream>
#include "tablero.h"
#include "fichas.h"

int main()
{
    // Prueba 1: tablero normal, posiciones que no cruzan byte.
    int filas = 5, columnas = 5;
    int bytesReservados = 0;
    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    colocarFicha(tablero, 0, 0, columnas, FICHA_A);
    colocarFicha(tablero, 0, 1, columnas, FICHA_F);
    colocarFicha(tablero, 1, 2, columnas, FICHA_C);

    std::cout << "Ficha en (0,0): " << (int)obtenerFicha(tablero, 0, 0, columnas) << std::endl;
    std::cout << "Ficha en (0,1): " << (int)obtenerFicha(tablero, 0, 1, columnas) << std::endl;
    std::cout << "Ficha en (1,2): " << (int)obtenerFicha(tablero, 1, 2, columnas) << std::endl;

    liberarTablero(tablero);

    // Prueba 2: tablero pequeño donde una ficha SI cruza entre bytes
    // (3 posiciones x 3 bits = 9 bits -> la tercera ficha empieza en el bit 6).
    int filas2 = 3, columnas2 = 1;
    int bytesReservados2 = 0;
    unsigned char* tablero2 = crearTablero(filas2, columnas2, bytesReservados2);

    colocarFicha(tablero2, 0, 0, columnas2, FICHA_B);
    colocarFicha(tablero2, 1, 0, columnas2, FICHA_D);
    colocarFicha(tablero2, 2, 0, columnas2, FICHA_F); // esta cruza entre byte0 y byte1

    std::cout << "Ficha partida en (2,0): " << (int)obtenerFicha(tablero2, 2, 0, columnas2) << std::endl;

    liberarTablero(tablero2);

    return 0;
}
