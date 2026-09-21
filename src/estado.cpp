#include "estado.h"

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

void registrarEliminacionUsuario() { eliminacionesUsuario = eliminacionesUsuario + 1; }
void sumarFichasEliminadas(int cantidad) { fichasEliminadasTotal = fichasEliminadasTotal + cantidad; }
void sumarCombosDetectados(int cantidad) { combosDetectados = combosDetectados + cantidad; }
void reiniciarCascadasJugada() { cascadasJugadaActual = 0; }
void incrementarCascadasJugada() { cascadasJugadaActual = cascadasJugadaActual + 1; }

void registrarPuntosPorBarrida(int fichasBarridas, int numeroCascada)
{
    int puntos = (fichasBarridas * 10) + (numeroCascada * 5);
    puntuacion = puntuacion + puntos;
}

int obtenerEliminacionesUsuario() { return eliminacionesUsuario; }
int obtenerFichasEliminadasTotal() { return fichasEliminadasTotal; }
int obtenerCombosDetectados() { return combosDetectados; }
int obtenerCascadasJugadaActual() { return cascadasJugadaActual; }
int obtenerPuntuacion() { return puntuacion; }
