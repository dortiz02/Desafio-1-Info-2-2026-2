#ifndef ESTADO_H
#define ESTADO_H

// Pone en cero todas las estadisticas de la partida. Debe llamarse una
// sola vez, al iniciar el juego.
void inicializarEstado();

// Registra que el usuario elimino una ficha manualmente.
void registrarEliminacionUsuario();

// Suma 'cantidad' al contador de fichas eliminadas en total (por el
// usuario o por combinaciones).
void sumarFichasEliminadas(int cantidad);

// Suma 'cantidad' al contador de combinaciones detectadas en la partida.
void sumarCombosDetectados(int cantidad);

// Pone en cero el contador de cascadas de la jugada actual. Se llama al
// inicio de cada jugada, antes de empezar el ciclo de cascada.
void reiniciarCascadasJugada();

// Incrementa en uno el contador de cascadas de la jugada actual.
void incrementarCascadasJugada();

// Suma 'puntos' a la puntuacion acumulada.
void sumarPuntuacion(int puntos);

// Funciones de consulta (getters) para mostrar el estado en pantalla.
int obtenerEliminacionesUsuario();
int obtenerFichasEliminadasTotal();
int obtenerCombosDetectados();
int obtenerCascadasJugadaActual();
int obtenerPuntuacion();

#endif // ESTADO_H
