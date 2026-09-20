#include "estado.h"

// Variables de alcance de archivo: solo son visibles y modificables desde
// las funciones de este modulo, imitando el encapsulamiento que normalmente
// daria una clase.
static int eliminacionesUsuario = 0;
static int fichasEliminadasTotal = 0;
static int combosDetectados = 0;
static int cascadasJugadaActual = 0;
static int puntuacion = 0;

void inicializarEstado()
{
    eliminacionesUsuario = 0;
    fichasEliminadasTotal = 0;
    combosDetectados = 0;
    cascadasJugadaActual = 0;
    puntuacion = 0;
}

void registrarEliminacionUsuario()
{
    eliminacionesUsuario = eliminacionesUsuario + 1;
}

void sumarFichasEliminadas(int cantidad)
{
    fichasEliminadasTotal = fichasEliminadasTotal + cantidad;
}

void sumarCombosDetectados(int cantidad)
{
    combosDetectados = combosDetectados + cantidad;
}

void reiniciarCascadasJugada()
{
    cascadasJugadaActual = 0;
}

void incrementarCascadasJugada()
{
    cascadasJugadaActual = cascadasJugadaActual + 1;
}

void sumarPuntuacion(int puntos)
{
    puntuacion = puntuacion + puntos;
}

int obtenerEliminacionesUsuario()
{
    return eliminacionesUsuario;
}

int obtenerFichasEliminadasTotal()
{
    return fichasEliminadasTotal;
}

int obtenerCombosDetectados()
{
    return combosDetectados;
}

int obtenerCascadasJugadaActual()
{
    return cascadasJugadaActual;
}

int obtenerPuntuacion()
{
    return puntuacion;
}
