#ifndef VISTA_H
#define VISTA_H

void mostrarTableroBinario(unsigned char* tablero, int bytesReservados);
void mostrarTableroFichas(unsigned char* tablero, int filas, int columnas);

// Imprime dimensiones, eliminaciones, fichas eliminadas, combos,
// cascadas y puntuacion. Se llama tras cada jugada.
void mostrarEstadoJuego(int filas, int columnas);

#endif // VISTA_H
