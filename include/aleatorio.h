#ifndef ALEATORIO_H
#define ALEATORIO_H

// Inicializa el generador de numeros aleatorios (llamar una sola vez al iniciar el programa).
void inicializarGeneradorAleatorio();

// Devuelve un codigo de ficha aleatorio (uno de los 6 tipos de ficha), con distribucion uniforme.
unsigned char generarFichaAleatoria();

#endif // ALEATORIO_H
