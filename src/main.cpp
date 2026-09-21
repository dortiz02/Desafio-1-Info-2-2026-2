#include <iostream>
#include <limits> // Para std::numeric_limits
#include "tablero.h"
#include "fichas.h"
#include "vista.h"
#include "aleatorio.h"
#include "estado.h"
#include "combinaciones.h"
#include "gravedad.h"

// Utilidad para limpiar el buffer de cin en caso de que el usuario introduzca caracteres no validos
void limpiarBufferEntrada() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

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
            registrarPuntosPorBarrida(fichasBarridas, obtenerCascadasJugadaActual());
        }
    } while (combosEnEstaRonda > 0);
}

void mostrarResumen(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);
    mostrarEstadoJuego(filas, columnas);
}

int main()
{
    inicializarGeneradorAleatorio();
    inicializarEstado();

    int filas = 0, columnas = 0;
    
    // VALIDACION: Asegurar dimensiones validas para el inicio del tablero.
    while (filas <= 0 || columnas <= 0) {
        std::cout << "Numero de filas del tablero (minimo 1): ";
        std::cin >> filas;
        limpiarBufferEntrada();
        
        std::cout << "Numero de columnas del tablero (minimo 1): ";
        std::cin >> columnas;
        limpiarBufferEntrada();
        
        if (filas <= 0 || columnas <= 0) {
            std::cout << "Error: Las dimensiones deben ser mayores a 0." << std::endl;
        }
    }

    int bytesReservados = 0;
    unsigned char* tablero = crearTablero(filas, columnas, bytesReservados);
    llenarTableroAleatorio(tablero, filas, columnas);

    // VALIDACION: Resolver cualquier combo que se haya generado puramente al azar en el llenado inicial.
    procesarCascadas(tablero, filas, columnas);

    mostrarTableroBinario(tablero, bytesReservados);
    mostrarTableroFichas(tablero, filas, columnas);

    bool jugando = true;
    while (jugando) {
        std::cout << std::endl << "1) Eliminar ficha  2) Agregar fila  3) Eliminar fila";
        std::cout << std::endl << "4) Agregar columna 5) Eliminar columna  6) Salir" << std::endl;

        int opcion;
        std::cin >> opcion;
        limpiarBufferEntrada();

        if (opcion == 1) {
            int filaSel, columnaSel;
            std::cout << "Fila (0.." << (filas - 1) << "): ";
            std::cin >> filaSel;
            std::cout << "Columna (0.." << (columnas - 1) << "): ";
            std::cin >> columnaSel;
            limpiarBufferEntrada();

            // VALIDACION: Limites de rango para eliminar ficha
            if (filaSel < 0 || filaSel >= filas || columnaSel < 0 || columnaSel >= columnas) {
                std::cout << "Error: Coordenadas fuera de rango." << std::endl;
                continue;
            }

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
            limpiarBufferEntrada();

            // VALIDACION: Limites de insercion de fila
            if (posicion < 0 || posicion > filas) {
                std::cout << "Error: Posicion fuera de rango." << std::endl;
                continue;
            }

            agregarFila(tablero, filas, bytesReservados, columnas, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 3) {
            // VALIDACION: No permitir quedarse sin filas
            if (filas <= 1) {
                std::cout << "Error: No se puede eliminar la ultima fila del tablero." << std::endl;
                continue;
            }
            
            int posicion;
            std::cout << "Fila a eliminar (0.." << (filas - 1) << "): ";
            std::cin >> posicion;
            limpiarBufferEntrada();

            // VALIDACION: Limites de eliminacion de fila
            if (posicion < 0 || posicion >= filas) {
                std::cout << "Error: Posicion fuera de rango." << std::endl;
                continue;
            }

            eliminarFila(tablero, filas, bytesReservados, columnas, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 4) {
            int posicion;
            std::cout << "Posicion de la nueva columna (0.." << columnas << "): ";
            std::cin >> posicion;
            limpiarBufferEntrada();

            // VALIDACION: Limites de insercion de columna
            if (posicion < 0 || posicion > columnas) {
                std::cout << "Error: Posicion fuera de rango." << std::endl;
                continue;
            }

            agregarColumna(tablero, filas, columnas, bytesReservados, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 5) {
            // VALIDACION: No permitir quedarse sin columnas
            if (columnas <= 1) {
                std::cout << "Error: No se puede eliminar la ultima columna del tablero." << std::endl;
                continue;
            }
            
            int posicion;
            std::cout << "Columna a eliminar (0.." << (columnas - 1) << "): ";
            std::cin >> posicion;
            limpiarBufferEntrada();

            // VALIDACION: Limites de eliminacion de columna
            if (posicion < 0 || posicion >= columnas) {
                std::cout << "Error: Posicion fuera de rango." << std::endl;
                continue;
            }

            eliminarColumna(tablero, filas, columnas, bytesReservados, posicion);
            procesarCascadas(tablero, filas, columnas);
            mostrarResumen(tablero, filas, columnas, bytesReservados);

        } else if (opcion == 6) {
            jugando = false;
        } else {
            std::cout << "Opcion invalida." << std::endl;
        }
    }

    liberarTablero(tablero);
    return 0;
}
