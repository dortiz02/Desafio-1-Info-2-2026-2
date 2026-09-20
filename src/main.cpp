#include <iostream>
#include "tablero.h"
#include "fichas.h"
#include "vista.h"
#include "aleatorio.h"

int main()
{
    inicializarGeneradorAleatorio();

    int filas, columnas;
    std::cout << "Numero de filas del tablero: ";
    std::cin >> filas;
    std::cout << "Numero de columnas del tablero: ";
    std::cin >> columnas;

    int bytesReservados = 0;
    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    llenarTableroAleatorio(tablero, filas, columnas);

    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);

    liberarTablero(tablero);

    return 0;
}
