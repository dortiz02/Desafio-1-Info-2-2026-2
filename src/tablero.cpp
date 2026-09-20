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

    // Se combina el byte actual con el siguiente en un valor de 16 bits,
    // pero solo cuando la ficha realmente cruza hacia el siguiente byte
    // (esto evita leer memoria fuera del bloque reservado cuando el
    // byte actual es el ultimo del tablero).
    unsigned int dosBytes = tablero[byteIndice];
    if (bitOffset > 5) {
        dosBytes = dosBytes | ((unsigned int)tablero[byteIndice + 1] << 8);
    }

    unsigned int mascara = (unsigned int)0b111 << bitOffset;
    unsigned int valor = (dosBytes & mascara) >> bitOffset;

    return (unsigned char)valor;
}

void colocarFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valorFicha)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * BITS_POR_FICHA;

    int byteIndice = bitInicial / 8;
    int bitOffset = bitInicial % 8;

    unsigned int mascaraFicha = (unsigned int)0b111 << bitOffset;
    unsigned int mascaraLimpiar = ~mascaraFicha;
    unsigned int valorDesplazado = (unsigned int)valorFicha << bitOffset;

    tablero[byteIndice] = (unsigned char)(tablero[byteIndice] & (mascaraLimpiar & 0xFF));
    tablero[byteIndice] = (unsigned char)(tablero[byteIndice] | (valorDesplazado & 0xFF));

    if (bitOffset > 5) {
        tablero[byteIndice + 1] = (unsigned char)(tablero[byteIndice + 1] & ((mascaraLimpiar >> 8) & 0xFF));
        tablero[byteIndice + 1] = (unsigned char)(tablero[byteIndice + 1] | ((valorDesplazado >> 8) & 0xFF));
    }
}
