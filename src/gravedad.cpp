#include "gravedad.h"
#include "tablero.h"
#include "fichas.h"
#include "aleatorio.h"

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

void generarNuevasFichas(unsigned char* tablero, int filas, int columnas)
{
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            unsigned char codigo = obtenerFicha(tablero, fila, columna, columnas);

            if (codigo == VACIO) {
                unsigned char nueva = generarFichaAleatoria();
                colocarFicha(tablero, fila, columna, columnas, nueva);
            }
        }
    }
}
