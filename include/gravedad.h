#ifndef GRAVEDAD_H
#define GRAVEDAD_H

// Para cada columna, desplaza las fichas no vacias hacia abajo, dejando
// las posiciones vacias agrupadas en la parte superior de la columna.
void aplicarGravedad(unsigned char* tablero, int filas, int columnas);

// Recorre todo el tablero y coloca una ficha aleatoria en cada posicion
// que este en estado VACIO. Se usa despues de aplicarGravedad, para
// recuperar las dimensiones completas del tablero.
void generarNuevasFichas(unsigned char* tablero, int filas, int columnas);

#endif // GRAVEDAD_H
