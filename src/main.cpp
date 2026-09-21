#include <iostream>
#include "tablero.h"
#include "fichas.h"
#include "vista.h"
#include "aleatorio.h"
#include "estado.h"
#include "combinaciones.h"
#include "gravedad.h"

void procesarCascadas(unsigned char* tablero, int filas, int columnas)
{
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
}

void mostrarResumen(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);

    std::cout << "Dimensiones: " << filas << "x" << columnas << std::endl;
    std::cout << "Eliminaciones del usuario: " << obtenerEliminacionesUsuario() << std::endl;
    std::cout << "Fichas eliminadas en total: " << obtenerFichasEliminadasTotal() << std::endl;
    std::cout << "Combinaciones detectadas: " << obtenerCombosDetectados() << std::endl;
    std::cout << "Cascadas en esta jugada: " << obtenerCascadasJugadaActual() << std::endl;
    std::cout << "Puntuacion: " << obtenerPuntuacion() << std::endl;
}

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
        std::cout << std::endl << "1) Eliminar ficha  2) Agregar fila  3) Eliminar fila";
        std::cout << std::endl << "4) Agregar columna 5) Eliminar columna  6) Salir" << std::endl;

        int opcion;
        std::cin >> opcion;

        if (opcion == 1) {
            int filaSel, columnaSel;
            std::cout << "Fila: ";
            std::cin >> filaSel;
            std::cout << "Columna: ";
            std::cin >> columnaSel;

            if (obtenerFicha(tablero, filaSel, columnaSel, columnas) == VACIO) {
                std::cout << "Esa posicion ya esta vacia." << std::endl;
                continue;
            }

            colocarFicha(tablero, filaSel, columnaSel, columnas, VACIO);
            registrarEliminacionUsuario();
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 2) {
            int posicion;
            std::cout << "Posicion de la nueva fila (0.." << filas << "): ";
            std::cin >> posicion;
            agregarFila(tablero, filas, bytesReservados, columnas, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 3) {
            int posicion;
            std::cout << "Fila a eliminar (0.." << (filas - 1) << "): ";
            std::cin >> posicion;
            eliminarFila(tablero, filas, bytesReservados, columnas, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 4) {
            int posicion;
            std::cout << "Posicion de la nueva columna (0.." << columnas << "): ";
            std::cin >> posicion;
            agregarColumna(tablero, filas, columnas, bytesReservados, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 5) {
            int posicion;
            std::cout << "Columna a eliminar (0.." << (columnas - 1) << "): ";
            std::cin >> posicion;
            eliminarColumna(tablero, filas, columnas, bytesReservados, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 6) {
            jugando = false;
        }
    }

    liberarTablero(tablero);
    return 0;
}
