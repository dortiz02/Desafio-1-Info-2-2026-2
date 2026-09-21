#include <iostream>
#include "tablero.h"
#include "fichas.h"
#include "vista.h"
#include "aleatorio.h"
#include "estado.h"
#include "combinaciones.h"
#include "gravedad.h"

int main()
{
    inicializarGeneradorAleatorio();
    inicializarEstado();

    int filas, columnas;
    std::cout << "Numero de filas del tablero: ";
    std::cin >> filas;
    std::cout << "Numero de columnas del tablero: ";
    std::cin >> columnas;

    int bytesReservados = 0;
    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);

    llenarTableroAleatorio(tablero, filas, columnas);

    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);

    bool jugando = true;
    while (jugando) {
        int filaSeleccionada, columnaSeleccionada;
        std::cout << "Fila a eliminar (-1 para salir): ";
        std::cin >> filaSeleccionada;

        if (filaSeleccionada == -1) {
            jugando = false;
            continue;
        }

        std::cout << "Columna a eliminar: ";
        std::cin >> columnaSeleccionada;

        unsigned char codigoActual = obtenerFicha(tablero, filaSeleccionada, columnaSeleccionada, columnas);

        if (codigoActual == VACIO) {
            std::cout << "Esa posicion ya esta vacia, elige otra." << std::endl;
            continue;
        }

        colocarFicha(tablero, filaSeleccionada, columnaSeleccionada, columnas, VACIO);
        registrarEliminacionUsuario();

        reiniciarCascadasJugada();

        int combosEnEstaRonda;
        do {
            aplicarGravedad(tablero, filas, columnas);
            generarNuevasFichas(tablero, filas, columnas);

            int combosH = detectarHorizontales(tablero, filas, columnas);
            int combosV = detectarVerticales(tablero, filas, columnas);
            combosEnEstaRonda = combosH + combosV;

            if (combosEnEstaRonda > 0) {
                sumarCombosDetectados(combosEnEstaRonda);
                incrementarCascadasJugada();

                int fichasBarridas = barrerMarcadas(tablero, filas, columnas);
                sumarFichasEliminadas(fichasBarridas);
            }

        } while (combosEnEstaRonda > 0);

        mostrarTableroBinario(tablero, bytesReservados);
        mostrarTableroFichas(tablero, filas, columnas);

        std::cout << "Dimensiones: " << filas << "x" << columnas << std::endl;
        std::cout << "Eliminaciones del usuario: " << obtenerEliminacionesUsuario() << std::endl;
        std::cout << "Fichas eliminadas en total: " << obtenerFichasEliminadasTotal() << std::endl;
        std::cout << "Combinaciones detectadas: " << obtenerCombosDetectados() << std::endl;
        std::cout << "Cascadas en esta jugada: " << obtenerCascadasJugadaActual() << std::endl;
        std::cout << "Puntuacion: " << obtenerPuntuacion() << std::endl;
    }

    liberarTablero(tablero);

    return 0;
}
