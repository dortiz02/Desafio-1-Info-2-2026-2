#ifndef FICHAS_H
#define FICHAS_H

// Códigos de 3 bits para cada posición del tablero.
// Con 3 bits hay 8 combinaciones posibles; se usan 6 para fichas
// y las 2 restantes para los estados VACIO y MARCADA.

const unsigned char FICHA_A = 0b000;
const unsigned char FICHA_B = 0b001;
const unsigned char FICHA_C = 0b010;
const unsigned char FICHA_D = 0b011;
const unsigned char FICHA_E = 0b100;
const unsigned char FICHA_F = 0b101;
const unsigned char VACIO   = 0b110; // posición sin ficha
const unsigned char MARCADA = 0b111; // pendiente de eliminar (uso interno)

const int BITS_POR_FICHA = 3;
const int CANTIDAD_TIPOS_FICHA = 6; // FICHA_A .. FICHA_F

#endif // FICHAS_H
