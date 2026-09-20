#include <iostream>
#include "tablero.h"
#include "fichas.h"

int main()
{
    int filas = 5, columnas = 5;
    int bytesReservados = 0;

    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    // Prueba manual: colocar algunas fichas y leerlas de vuelta
    colocarFicha(tablero, 0, 0, columnas, FICHA_A);
    colocarFicha(tablero, 0, 1, columnas, FICHA_F);
    colocarFicha(tablero, 1, 2, columnas, FICHA_C);

    std::cout << "Ficha en (0,0): " << (int)obtenerFicha(tablero, 0, 0, columnas) << std::endl;
    std::cout << "Ficha en (0,1): " << (int)obtenerFicha(tablero, 0, 1, columnas) << std::endl;
    std::cout << "Ficha en (1,2): " << (int)obtenerFicha(tablero, 1, 2, columnas) << std::endl;

    std::cout << "Bytes crudos: ";
    for (int i = 0; i < bytesReservados; i++) {
        for (int b = 7; b >= 0; b--) {
            std::cout << ((tablero[i] >> b) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    liberarTablero(tablero);

    return 0;
}
