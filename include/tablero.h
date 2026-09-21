#ifndef TABLERO_H
#define TABLERO_H

// Crea un tablero de 'filas' x 'columnas', reservando la cantidad minima
// de bytes necesaria para almacenar 3 bits por posicion.
unsigned char* crearTablero(int filas, int columnas, int &bytesReservados);

// Libera la memoria asociada a un tablero.
void liberarTablero(unsigned char* tablero);

// Obtiene el codigo de 3 bits almacenado en (fila, columna).
unsigned char obtenerFicha(unsigned char* tablero, int fila, int columna, int columnas);

// Escribe el codigo de 3 bits 'valorFicha' en (fila, columna).
void colocarFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valorFicha);

// Llena todas las posiciones del tablero con fichas aleatorias.
void llenarTableroAleatorio(unsigned char* tablero, int filas, int columnas);

// Inserta una fila vacia (todo VACIO) en la posicion indicada (0..filas).
// Reasigna la memoria al tamaño minimo necesario para las nuevas dimensiones.
void agregarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion);

// Elimina la fila en la posicion indicada (0..filas-1).
// Por ahora siempre reasigna la memoria al tamaño minimo exacto; la
// politica de conservar el bloque viejo se agrega mas adelante.
void eliminarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion);

#endif // TABLERO_H
