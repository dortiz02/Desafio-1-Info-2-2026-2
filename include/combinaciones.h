#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Recorre el tablero por filas y marca (con el codigo MARCADA) las fichas
// que forman parte de una secuencia horizontal de 3 o mas fichas iguales.
// Devuelve la cantidad de combinaciones horizontales encontradas.
int detectarHorizontales(unsigned char* tablero, int filas, int columnas);

// Recorre el tablero por columnas y marca (con el codigo MARCADA) las
// fichas que forman parte de una secuencia vertical de 3 o mas fichas
// iguales. Devuelve la cantidad de combinaciones verticales encontradas.
int detectarVerticales(unsigned char* tablero, int filas, int columnas);

// Recorre el tablero completo y convierte toda ficha MARCADA en VACIO.
// Una ficha marcada por combo horizontal Y vertical a la vez solo se
// cuenta una vez, porque el barrido revisa cada posicion una sola vez.
// Devuelve la cantidad de fichas que fueron barridas (eliminadas).
int barrerMarcadas(unsigned char* tablero, int filas, int columnas);

#endif // COMBINACIONES_H
