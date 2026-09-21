#ifndef ESTADO_H
#define ESTADO_H

void inicializarEstado();
void registrarEliminacionUsuario();
void sumarFichasEliminadas(int cantidad);
void sumarCombosDetectados(int cantidad);
void reiniciarCascadasJugada();
void incrementarCascadasJugada();

// Calcula y suma los puntos de una barrida: 10 puntos por ficha eliminada
// mas un bono de 5 puntos por cada cascada ya ocurrida en esta jugada
// (para premiar cascadas largas). Se llama justo despues de barrerMarcadas.
void registrarPuntosPorBarrida(int fichasBarridas, int numeroCascada);

int obtenerEliminacionesUsuario();
int obtenerFichasEliminadasTotal();
int obtenerCombosDetectados();
int obtenerCascadasJugadaActual();
int obtenerPuntuacion();

#endif // ESTADO_H
