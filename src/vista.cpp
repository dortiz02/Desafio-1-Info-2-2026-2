#include <iostream>
#include "vista.h"
#include "tablero.h"
#include "fichas.h"
#include "estado.h"

char caracterDeFicha(unsigned char codigo)
{
    switch (codigo) {
        case FICHA_A: return 'A';
        case FICHA_B: return 'B';
        case FICHA_C: return 'C';
        case FICHA_D: return 'D';
        case FICHA_E: return 'E';
        case FICHA_F: return 'F';
        case VACIO:   return '.';
        case MARCADA: return 'X';
        default:      return '?';
    }
}

void mostrarTableroBinario(unsigned char* tablero, int bytesReservados)
{
    std::cout << "Tablero (binario, " << bytesReservados << " bytes): " << std::endl;
    for (int i = 0; i < bytesReservados; i++) {
        for (int b = 7; b >= 0; b--) {
            std::cout << ((tablero[i] >> b) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void mostrarTableroFichas(unsigned char* tablero, int filas, int columnas)
{
    std::cout << "Tablero (fichas):" << std::endl;
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            std::cout << caracterDeFicha(obtenerFicha(tablero, fila, columna, columnas)) << " ";
        }
        std::cout << std::endl;
    }
}

void mostrarEstadoJuego(int filas, int columnas)
{
    std::cout << "Dimensiones: " << filas << "x" << columnas << std::endl;
    std::cout << "Eliminaciones del usuario: " << obtenerEliminacionesUsuario() << std::endl;
    std::cout << "Fichas eliminadas en total: " << obtenerFichasEliminadasTotal() << std::endl;
    std::cout << "Combinaciones detectadas: " << obtenerCombosDetectados() << std::endl;
    std::cout << "Cascadas en esta jugada: " << obtenerCascadasJugadaActual() << std::endl;
    std::cout << "Puntuacion: " << obtenerPuntuacion() << std::endl;
}
