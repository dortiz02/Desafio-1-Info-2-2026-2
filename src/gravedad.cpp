#include "gravedad.h"
#include "tablero.h"
#include "fichas.h"

void aplicarGravedad(unsigned char* tablero, int filas, int columnas)
{
    for (int columna = 0; columna < columnas; columna++) {
        int filaEscritura = filas - 1; // desde abajo hacia arriba

        for (int filaLectura = filas - 1; filaLectura >= 0; filaLectura--) {
            unsigned char codigo = obtenerFicha(tablero, filaLectura, columna, columnas);

            if (codigo != VACIO) {
                if (filaLectura != filaEscritura) {
                    colocarFicha(tablero, filaEscritura, columna, columnas, codigo);
                    colocarFicha(tablero, filaLectura, columna, columnas, VACIO);
                }
                filaEscritura = filaEscritura - 1;
            }
        }
    }
}
