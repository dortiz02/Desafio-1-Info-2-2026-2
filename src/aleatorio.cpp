#include <random>
#include "aleatorio.h"
#include "fichas.h"

// Motor de numeros aleatorios y distribucion, con alcance de archivo (no se puede usar una clase propia para envolver esto, asi que se mantienen como variables estaticas del modulo).
static std::mt19937 generador;
static std::uniform_int_distribution<int> distribucion(0, CANTIDAD_TIPOS_FICHA - 1);

void inicializarGeneradorAleatorio()
{
    std::random_device semilla;
    generador.seed(semilla());
}

unsigned char generarFichaAleatoria()
{
    int numero = distribucion(generador);
    return (unsigned char)numero;
}
