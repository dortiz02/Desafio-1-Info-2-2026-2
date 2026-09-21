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
void agregarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion);

// Elimina la fila en la posicion indicada (0..filas-1). La memoria fisica
// solo se reduce si la ocupacion resultante cae debajo del 65% de la
// capacidad actualmente reservada; en caso contrario se conserva el
// bloque actual y solo cambian las dimensiones logicas.
void eliminarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion);

// Inserta una columna vacia (todo VACIO) en la posicion indicada (0..columnas).
void agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &bytesReservados, int posicion);

// Elimina la columna en la posicion indicada (0..columnas-1). Misma
// politica de capacidad que eliminarFila.
void eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &bytesReservados, int posicion);

int obtenerCapacidadReservada();

#endif // TABLERO_H
