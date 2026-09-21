#include "tablero.h"
#include "fichas.h"
#include "aleatorio.h"

// Capacidad fisica actualmente reservada (en bytes). Variable de alcance
// de archivo, siguiendo el mismo patron usado en el modulo estado: sirve
// para no tener que pasarla como parametro en cada funcion del modulo.
static int capacidadReservada = 0;

static int calcularBytesNecesarios(int filas, int columnas)
{
    int totalBits = filas * columnas * BITS_POR_FICHA;
    return (totalBits + 7) / 8;
}

unsigned char* crearTablero(int filas, int columnas, int &bytesReservados)
{
    bytesReservados = calcularBytesNecesarios(filas, columnas);
    capacidadReservada = bytesReservados;

    unsigned char* tablero = new unsigned char[bytesReservados];

    for (int i = 0; i < bytesReservados; i++) {
        tablero[i] = 0;
    }

    return tablero;
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}

unsigned char obtenerFicha(unsigned char* tablero, int fila, int columna, int columnas)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * BITS_POR_FICHA;

    int byteIndice = bitInicial / 8;
    int bitOffset = bitInicial % 8;

    unsigned int dosBytes = tablero[byteIndice];
    if (bitOffset > 5) {
        dosBytes = dosBytes | ((unsigned int)tablero[byteIndice + 1] << 8);
    }

    unsigned int mascara = (unsigned int)0b111 << bitOffset;
    unsigned int valor = (dosBytes & mascara) >> bitOffset;

    return (unsigned char)valor;
}

void colocarFicha(unsigned char* tablero, int fila, int columna, int columnas, unsigned char valorFicha)
{
    int indice = fila * columnas + columna;
    int bitInicial = indice * BITS_POR_FICHA;

    int byteIndice = bitInicial / 8;
    int bitOffset = bitInicial % 8;

    unsigned int mascaraFicha = (unsigned int)0b111 << bitOffset;
    unsigned int mascaraLimpiar = ~mascaraFicha;
    unsigned int valorDesplazado = (unsigned int)valorFicha << bitOffset;

    tablero[byteIndice] = (unsigned char)(tablero[byteIndice] & (mascaraLimpiar & 0xFF));
    tablero[byteIndice] = (unsigned char)(tablero[byteIndice] | (valorDesplazado & 0xFF));

    if (bitOffset > 5) {
        tablero[byteIndice + 1] = (unsigned char)(tablero[byteIndice + 1] & ((mascaraLimpiar >> 8) & 0xFF));
        tablero[byteIndice + 1] = (unsigned char)(tablero[byteIndice + 1] | ((valorDesplazado >> 8) & 0xFF));
    }
}

void llenarTableroAleatorio(unsigned char* tablero, int filas, int columnas)
{
    for (int fila = 0; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            unsigned char ficha = generarFichaAleatoria();
            colocarFicha(tablero, fila, columna, columnas, ficha);
        }
    }
}

void agregarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion)
{
    int nuevasFilas = filas + 1;
    int nuevosBytes = calcularBytesNecesarios(nuevasFilas, columnas);

    unsigned char* nuevoTablero = new unsigned char[nuevosBytes];
    for (int i = 0; i < nuevosBytes; i++) {
        nuevoTablero[i] = 0;
    }

    for (int filaNueva = 0; filaNueva < nuevasFilas; filaNueva++) {
        for (int columna = 0; columna < columnas; columna++) {
            if (filaNueva < posicion) {
                unsigned char valor = obtenerFicha(tablero, filaNueva, columna, columnas);
                colocarFicha(nuevoTablero, filaNueva, columna, columnas, valor);
            } else if (filaNueva == posicion) {
                colocarFicha(nuevoTablero, filaNueva, columna, columnas, VACIO);
            } else {
                unsigned char valor = obtenerFicha(tablero, filaNueva - 1, columna, columnas);
                colocarFicha(nuevoTablero, filaNueva, columna, columnas, valor);
            }
        }
    }

    delete[] tablero;
    tablero = nuevoTablero;
    filas = nuevasFilas;
    bytesReservados = nuevosBytes;
    capacidadReservada = nuevosBytes; // al agregar, siempre se crece exacto
}

void eliminarFila(unsigned char* &tablero, int &filas, int &bytesReservados, int columnas, int posicion)
{
    int nuevasFilas = filas - 1;
    int bytesNecesarios = calcularBytesNecesarios(nuevasFilas, columnas);
    double ocupacion = (double)bytesNecesarios / (double)capacidadReservada;

    if (ocupacion < 0.65) {
        unsigned char* nuevoTablero = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) nuevoTablero[i] = 0;

        for (int filaNueva = 0; filaNueva < nuevasFilas; filaNueva++) {
            for (int columna = 0; columna < columnas; columna++) {
                int filaOrigen = (filaNueva < posicion) ? filaNueva : filaNueva + 1;
                unsigned char valor = obtenerFicha(tablero, filaOrigen, columna, columnas);
                colocarFicha(nuevoTablero, filaNueva, columna, columnas, valor);
            }
        }

        delete[] tablero;
        tablero = nuevoTablero;
        capacidadReservada = bytesNecesarios;
    } else {
        unsigned char* temporal = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) temporal[i] = 0;

        for (int filaNueva = 0; filaNueva < nuevasFilas; filaNueva++) {
            for (int columna = 0; columna < columnas; columna++) {
                int filaOrigen = (filaNueva < posicion) ? filaNueva : filaNueva + 1;
                unsigned char valor = obtenerFicha(tablero, filaOrigen, columna, columnas);
                colocarFicha(temporal, filaNueva, columna, columnas, valor);
            }
        }

        for (int i = 0; i < bytesNecesarios; i++) tablero[i] = temporal[i];
        delete[] temporal;
    }

    filas = nuevasFilas;
    bytesReservados = bytesNecesarios;
}
void agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &bytesReservados, int posicion)
{
    int columnasViejas = columnas;
    int nuevasColumnas = columnas + 1;
    int nuevosBytes = calcularBytesNecesarios(filas, nuevasColumnas);

    unsigned char* nuevoTablero = new unsigned char[nuevosBytes];
    for (int i = 0; i < nuevosBytes; i++) {
        nuevoTablero[i] = 0;
    }

    for (int fila = 0; fila < filas; fila++) {
        for (int columnaNueva = 0; columnaNueva < nuevasColumnas; columnaNueva++) {
            if (columnaNueva < posicion) {
                unsigned char valor = obtenerFicha(tablero, fila, columnaNueva, columnasViejas);
                colocarFicha(nuevoTablero, fila, columnaNueva, nuevasColumnas, valor);
            } else if (columnaNueva == posicion) {
                colocarFicha(nuevoTablero, fila, columnaNueva, nuevasColumnas, VACIO);
            } else {
                unsigned char valor = obtenerFicha(tablero, fila, columnaNueva - 1, columnasViejas);
                colocarFicha(nuevoTablero, fila, columnaNueva, nuevasColumnas, valor);
            }
        }
    }

    delete[] tablero;
    tablero = nuevoTablero;
    columnas = nuevasColumnas;
    bytesReservados = nuevosBytes;
    capacidadReservada = nuevosBytes; // al agregar, siempre se crece exacto
}

void eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &bytesReservados, int posicion)
{
    int columnasViejas = columnas;
    int nuevasColumnas = columnas - 1;
    int bytesNecesarios = calcularBytesNecesarios(filas, nuevasColumnas);
    double ocupacion = (double)bytesNecesarios / (double)capacidadReservada;

    if (ocupacion < 0.65) {
        unsigned char* nuevoTablero = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) nuevoTablero[i] = 0;

        for (int fila = 0; fila < filas; fila++) {
            for (int columnaNueva = 0; columnaNueva < nuevasColumnas; columnaNueva++) {
                int columnaOrigen = (columnaNueva < posicion) ? columnaNueva : columnaNueva + 1;
                unsigned char valor = obtenerFicha(tablero, fila, columnaOrigen, columnasViejas);
                colocarFicha(nuevoTablero, fila, columnaNueva, nuevasColumnas, valor);
            }
        }

        delete[] tablero;
        tablero = nuevoTablero;
        capacidadReservada = bytesNecesarios;
    } else {
        unsigned char* temporal = new unsigned char[bytesNecesarios];
        for (int i = 0; i < bytesNecesarios; i++) temporal[i] = 0;

        for (int fila = 0; fila < filas; fila++) {
            for (int columnaNueva = 0; columnaNueva < nuevasColumnas; columnaNueva++) {
                int columnaOrigen = (columnaNueva < posicion) ? columnaNueva : columnaNueva + 1;
                unsigned char valor = obtenerFicha(tablero, fila, columnaOrigen, columnasViejas);
                colocarFicha(temporal, fila, columnaNueva, nuevasColumnas, valor);
            }
        }

        for (int i = 0; i < bytesNecesarios; i++) tablero[i] = temporal[i];
        delete[] temporal;
    }

    columnas = nuevasColumnas;
    bytesReservados = bytesNecesarios;
}

int obtenerCapacidadReservada()
{
    return capacidadReservada;
}
