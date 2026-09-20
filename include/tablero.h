#ifndef TABLERO_H
#define TABLERO_H

// Crea un tablero de filas x columnas, reservando la cantidad mínima
// de bytes necesaria para almacenar 3 bits por posición.
// Devuelve el puntero al bloque de memoria reservado y, por referencia,
// la cantidad de bytes reservados (capacidad física inicial).
unsigned char* crearTablero(int filas, int columnas, int &bytesReservados);

// Libera la memoria asociada a un tablero.
void liberarTablero(unsigned char* tablero);

#endif // TABLERO_H
