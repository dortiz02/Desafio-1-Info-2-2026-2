#include "tablero.h"
#include "fichas.h"

unsigned char* crearTablero(int filas, int columnas, int &bytesReservados)
{
    int totalBits = filas * columnas * BITS_POR_FICHA;
    bytesReservados = (totalBits + 7) / 8; // redondeo hacia arriba

    unsigned char* tablero = new unsigned char[bytesReservados];

    for (int i = 0; i < bytesReservados; i++) {
        tablero[i] = 0;
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}

unsigned char obtenerFicha(unsigned char* tablero, int fila, int columna, int columnas)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * BITS_POR_FICHA;

    int byteIndice = bitInicial / 8;
    int bitOffset = bitInicial % 8;

    unsigned char mascara = 0b111 << bitOffset;
    unsigned char valor = (tablero[byteIndice] & mascara) >> bitOffset;

    return valor;
}

void colocarFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valorFicha)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * BITS_POR_FICHA;

    int byteIndice = bitInicial / 8;
    int bitOffset = bitInicial % 8;

    unsigned char mascaraLimpiar = ~(0b111 << bitOffset);
    tablero[byteIndice] = tablero[byteIndice] & mascaraLimpiar;
    tablero[byteIndice] = tablero[byteIndice] | (valorFicha << bitOffset);
}
