#include "tablero.h"
#include "fichas.h"

unsigned char* crearTablero(int filas, int columnas, int &bytesReservados)
{
    int totalBits = filas * columnas * BITS_POR_FICHA;
    bytesReservados = (totalBits + 7) / 8; // redondeo hacia arriba

    unsigned char* tablero = new unsigned char[bytesReservados];

    // Por ahora se deja todo en cero; el llenado con fichas aleatorias
    // se agrega en un commit posterior.
    for (int i = 0; i < bytesReservados; i++) {
        tablero[i] = 0;
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}
