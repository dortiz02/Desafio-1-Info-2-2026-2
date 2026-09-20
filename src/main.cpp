#include <iostream>
#include "tablero.h"
#include "fichas.h"
#include "vista.h"

int main()
{
    int filas = 4, columnas = 4;
    int bytesReservados = 0;
    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    // Llenado manual de prueba (el llenado aleatorio se agrega en el proximo commit)
    unsigned char valores[16] = {
        FICHA_A, FICHA_B, FICHA_C, FICHA_D,
        FICHA_E, FICHA_F, FICHA_A, VACIO,
        FICHA_B, FICHA_C, MARCADA, FICHA_E,
        FICHA_F, FICHA_A, FICHA_B, FICHA_C
    };

    int contador = 0;
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            colocarFicha(tablero, fila, columna, columnas, valores[contador]);
            contador++;
        }
    }

    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);

    liberarTablero(tablero);

    return 0;
}
