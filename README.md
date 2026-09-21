# Sweet Crush — Desafío 1 (Informática II, 2026-2)

Juego tipo Candy Crush para Qt Console, hecho en C++. Las fichas se guardan en 3 bits por posición y la memoria del tablero se administra a mano. El código no usa clases, ni STL, ni string.

## Compilar

1. Abrí `main.pro` en Qt Creator.
2. Elegí un kit de escritorio que compile C++17.
3. Compilá y ejecutá con Ctrl+R.

## Cómo se juega

Al arrancar, el programa pide filas y columnas. Después aparece un menú:

1. Eliminar una ficha (pide fila y columna).
2. Agregar una fila (posición 0..filas).
3. Eliminar una fila (posición 0..filas-1).
4. Agregar una columna (posición 0..columnas).
5. Eliminar una columna (posición 0..columnas-1).
6. Salir.

Cada acción imprime el tablero en binario, el tablero con fichas y las estadísticas de la partida.

## Archivos

- `main.cpp`: arranque y menú.
- `fichas.h`: códigos de 3 bits para fichas y estados.
- `tablero.h/.cpp`: reserva, acceso y redimensionamiento.
- `vista.h/.cpp`: impresión del tablero y del estado.
- `combinaciones.h/.cpp`: detección y barrido de combinaciones.
- `gravedad.h/.cpp`: caída y relleno de fichas.
- `aleatorio.h/.cpp`: fichas aleatorias con distribución uniforme.
- `estado.h/.cpp`: estadísticas y puntuación.
