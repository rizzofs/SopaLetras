#include <stdio.h>
#include <string.h>

#define FILAS 5
#define COLS 5

// Colores ANSI
#define ROJO "\033[1;31m"
#define BLANCO "\033[0m"

int main() {
    char sopa[FILAS][COLS] = {
        {'C', 'C', 'S', 'A', 'X'},
        {'X', 'O', 'X', 'X', 'X'},
        {'X', 'S', 'X', 'X', 'X'},
        {'X', 'A', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X'}
    };

    // Coordenadas de la palabra "COSA" (suponiendo vertical)
    int palabra_len = 4;
    int coords[][2] = {
        {0, 1}, // C
        {1, 1}, // O
        {2, 1}, // S
        {3, 1}  // A
    };

    // Imprimir la sopa con colores
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            int es_palabra = 0;
            for (int k = 0; k < palabra_len; k++) {
                if (coords[k][0] == i && coords[k][1] == j) {
                    es_palabra = 1;
                    break;
                }
            }
            if (es_palabra) {
                printf(ROJO "%c " BLANCO, sopa[i][j]);
            } else {
                printf("%c ", sopa[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
// Compilar
//gcc -o  Color color.c
//Ejecutar
// ./color