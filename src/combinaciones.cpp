#include "combinaciones.h"
#include "tablero.h"
#include "fichas.h"

// Indica si un codigo corresponde a una ficha real (no vacio, no marcada).
bool esFichaValida(unsigned char codigo)
{
    return codigo <= FICHA_F; // FICHA_A..FICHA_F son los codigos 0 a 5
}

int detectarHorizontales(unsigned char* tablero, int filas, int columnas)
{
    int combosEncontrados = 0;

    for (int fila = 0; fila < filas; fila++) {
        int columna = 0;
        while (columna < columnas) {
            unsigned char tipoActual = obtenerFicha(tablero, fila, columna, columnas);

            if (!esFichaValida(tipoActual)) {
                columna = columna + 1;
                continue;
            }

            int inicio = columna;
            int largo = 1;

            while (columna + 1 < columnas &&
                   obtenerFicha(tablero, fila, columna + 1, columnas) == tipoActual) {
                columna = columna + 1;
                largo = largo + 1;
            }

            if (largo >= 3) {
                for (int c = inicio; c <= columna; c++) {
                    colocarFicha(tablero, fila, c, columnas, MARCADA);
                }
                combosEncontrados = combosEncontrados + 1;
            }

            columna = columna + 1;
        }
    }

    return combosEncontrados;
}

int detectarVerticales(unsigned char* tablero, int filas, int columnas)
{
    int combosEncontrados = 0;

    for (int columna = 0; columna < columnas; columna++) {
        int fila = 0;
        while (fila < filas) {
            unsigned char tipoActual = obtenerFicha(tablero, fila, columna, columnas);

            if (!esFichaValida(tipoActual)) {
                fila = fila + 1;
                continue;
            }

            int inicio = fila;
            int largo = 1;

            while (fila + 1 < filas &&
                   obtenerFicha(tablero, fila + 1, columna, columnas) == tipoActual) {
                fila = fila + 1;
                largo = largo + 1;
            }

            if (largo >= 3) {
                for (int f = inicio; f <= fila; f++) {
                    colocarFicha(tablero, f, columna, columnas, MARCADA);
                }
                combosEncontrados = combosEncontrados + 1;
            }

            fila = fila + 1;
        }
    }

    return combosEncontrados;
}
