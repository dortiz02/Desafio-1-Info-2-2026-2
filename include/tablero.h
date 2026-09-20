#ifndef TABLERO_H
#define TABLERO_H

// Crea un tablero de filas x columnas, reservando la cantidad mínima
// de bytes necesaria para almacenar 3 bits por posición.
unsigned char* crearTablero(int filas, int columnas, int &bytesReservados);

// Libera la memoria asociada a un tablero.
void liberarTablero(unsigned char* tablero);

// Obtiene el codigo de 3 bits almacenado en (fila, columna).
unsigned char obtenerFicha(unsigned char* tablero, int fila, int columna, int columnas);

// Escribe el codigo de 3 bits valorFicha en (fila, columna).
void colocarFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valorFicha);

#endif // TABLERO_H
