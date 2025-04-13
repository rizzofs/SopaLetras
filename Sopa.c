#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define TAMANIO_MAXIMO_GRILLA 100
#define TAMANIO_MAXIMO_PALABRA 50
#define MAXIMO_PALABRAS 100

struct Posicion {
    unsigned int fila;
    unsigned int columna;
};

struct ResultadoPalabra {
    char palabra[TAMANIO_MAXIMO_PALABRA];
    bool encontrada;
    struct Posicion inicio;
    struct Posicion fin;
};

//MATRIZ
struct SopaDeLetras {
    char grilla[TAMANIO_MAXIMO_GRILLA][TAMANIO_MAXIMO_GRILLA];
    int filas;
    int columnas;
    char palabras[MAXIMO_PALABRAS][TAMANIO_MAXIMO_PALABRA];
    int cantidad_palabras;
    int longitud[MAXIMO_PALABRAS]; //agregue esto
};

// Función para leer el archivo
void leerArchivo(const char *archivo, struct SopaDeLetras *sopa) {
    int fila = 0;
    int columna = 0;
    char letra;
    FILE *f = fopen(archivo, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fscanf(f, "%c", &letra);
    while (!feof(f) && letra != '\n') {
        while (!feof(f) && letra != '\n') {
            sopa->grilla[fila][columna] = letra;
            columna++;
            fscanf(f, "%c", &letra);
        }
        sopa->columnas = columna; // Cantidad de columnas
        fila++;
        columna = 0;
        fscanf(f, "%c", &letra);
    }
    sopa->filas = fila; // Cantidad de filas

    fscanf(f, "%c", &letra);
    while (!feof(f)) {
        char palabra[TAMANIO_MAXIMO_PALABRA];
        int indice = 0;

        while (!feof(f) && letra != '\n') {
            if (letra == '#') {
                while (!feof(f) && letra != '\n') {
                    fscanf(f, "%c", &letra);
                }
            } else {
                palabra[indice] = letra;
                indice++;
                fscanf(f, "%c", &letra);
            }
        }

        palabra[indice] = '\0';
        if (indice > 0 && sopa->cantidad_palabras < MAXIMO_PALABRAS) { // Ignorar palabras vacías
            strcpy(sopa->palabras[sopa->cantidad_palabras], palabra);
            sopa->longitud[sopa->cantidad_palabras] = strlen(palabra);//Almaceno la longitud de cada palabra
            sopa->cantidad_palabras++;
                    


        }
        fscanf(f, "%c", &letra);
        
    }
    fclose(f);
}

// Función para imprimir la matriz.
void imprimirMatriz(struct SopaDeLetras *sopa) {
    printf("Sopa de letras:\n");
    for (int i = 0; i < sopa->filas; i++) {
        for (int j = 0; j < sopa->columnas; j++) {
            printf("%c ", sopa->grilla[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir palabras almacenadas y sus longitudes.
void imprimirPalabras(struct SopaDeLetras *sopa) {
    printf("Vector de palabras almacenadas y longitudes:\n");
    for (int i = 0; i < sopa->cantidad_palabras; i++) {
        printf("Palabra: %s, Longitud: %d\n", sopa->palabras[i], sopa->longitud[i]);
    }
}

//Función recursiva para encontrar la palabra.
bool buscarPalabra(struct SopaDeLetras *sopa, int filaSopa, int columnaSopa, int filaPalabra, int columnaPalabra, int direccion){
    char letraPalabra = sopa->palabras[filaPalabra][columnaPalabra];
    char letraSopa = sopa->grilla[filaSopa][columnaSopa];
    
    //  Caso Base: Llego al final de la cadena de la palabra que buscaba
    if (letraPalabra == '\0'){
        return true;
    }   

    //  Caso Base: Chequear límites
    if (filaSopa < 0 || columnaSopa < 0 || columnaSopa >= sopa->filas|| filaSopa >= sopa->columnas)
        return false;

    // Comprobar si la letra de la palabra es igual a la letra que tiene la sopa
    if (letraPalabra == letraSopa) {
        if (direccion == 0){
            return (buscarPalabra(sopa, filaSopa-1, columnaSopa, filaPalabra, columnaPalabra+1, 1)|| //Vertical Arriba
            buscarPalabra(sopa, filaSopa-1, columnaSopa+1, filaPalabra, columnaPalabra+1, 2)|| // Diagonal Derecha Arriba
            buscarPalabra(sopa, filaSopa, columnaSopa+1, filaPalabra, columnaPalabra+1, 3)|| // Horizontal Derecha
            buscarPalabra(sopa, filaSopa+1, columnaSopa+1, filaPalabra, columnaPalabra+1, 4)|| // Diagonal Derecha Abajo
            buscarPalabra(sopa, filaSopa+1, columnaSopa, filaPalabra, columnaPalabra+1, 5)|| //Vertical Abajo
            buscarPalabra(sopa, filaSopa+1, columnaSopa-1, filaPalabra, columnaPalabra+1, 6)|| //Diagonal Izquierda Abajo
            buscarPalabra(sopa, filaSopa, columnaSopa-1, filaPalabra, columnaPalabra+1, 7)|| //Horizontal Izquierda
            buscarPalabra(sopa, filaSopa-1, columnaSopa-1, filaPalabra, columnaPalabra+1, 8) // Diagonal Izquierda Arriba
            );
        } else {
            switch (direccion) //Creo que nos falta agregar un return en cada caso. 
            {
            case 1: // Vertical Arriba
                buscarPalabra(sopa, filaSopa-1, columnaSopa, filaPalabra, columnaPalabra+1, 1);
                break;
            case 2:// Diagonal Derecha Arriba
                buscarPalabra(sopa, filaSopa-1, columnaSopa+1, filaPalabra, columnaPalabra+1, 2);
                break;
            case 3:// Horizontal Derecha
                buscarPalabra(sopa, filaSopa, columnaSopa+1, filaPalabra, columnaPalabra+1, 3);
                break;
            case 4: // Diagonal Derecha Abajo
                buscarPalabra(sopa, filaSopa+1, columnaSopa+1, filaPalabra, columnaPalabra+1, 4);
                break;
            case 5://Vertical Abajo
                buscarPalabra(sopa, filaSopa+1, columnaSopa, filaPalabra, columnaPalabra+1, 5);
                break;
            case 6://Diagonal Izquierda Abajo
                buscarPalabra(sopa, filaSopa+1, columnaSopa-1, filaPalabra, columnaPalabra+1, 6);
                break;
            case 7://Horizontal Izquierda
                buscarPalabra(sopa, filaSopa, columnaSopa-1, filaPalabra, columnaPalabra+1, 7);
                break;
            case 8:// Diagonal Izquierda Arriba
                buscarPalabra(sopa, filaSopa-1, columnaSopa-1, filaPalabra, columnaPalabra+1, 8);
                break;
            
            default:
                break;
            }
        }
    } else {
        return false;
    }
}


//Función para generar el archivo de salida.  

int main() {
    struct SopaDeLetras sopa;
    sopa.filas = 0;
    sopa.columnas = 0;
    sopa.cantidad_palabras = 0;

    leerArchivo("entrada.txt", &sopa);

    int opcion;

    do {
        printf("*****************************\n");
        printf("************MENU***************\n");
        printf("*******************************\n");
        printf("1 - Mostrar sopa de letras\n");
        printf("2 - Mostrar Palabras\n");
        printf("3 - Buscar Compas\n");
        printf("0 - Salir\n");
        printf("Ingrese la opcion deseada: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada inválida. Por favor, ingrese un número.\n");
            while (getchar() != '\n');
            continue;
        }

        bool x;
        switch (opcion) {
            case 0:
                printf("Saliendo del programa...\n");
                break;
            case 1:
                imprimirMatriz(&sopa);
                break;
            case 2:
                imprimirPalabras(&sopa);
                break;
            case 3:
                //Medir tiempo de ejecucion
                //bool buscarPalabra(struct SopaDeLetras *sopa, int filaSopa, int columnaSopa, int filaPalabra, int columnaPalabra, int direccion){
                x = buscarPalabra(&sopa, 3, 4, 0, 0, 0);
                printf("valor de x: %d\n", x);
            break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}

// Compilar
//gcc -o Sopa Sopa.c
//Ejecutar
// ./sopa

// bool resolver_laberinto_aux(struct Laberinto *lab, const int i, const int j) {
//     imprimir_laberinto(lab);

//     Chequear límites
//     if (i < 0 || j < 0 || i >= lab->alto || j >= lab->ancho)
//         return false;

//     Chequear si chocamos con una pared o ya visitamos
//     if (lab->laberinto[i][j] == 'P' || lab->laberinto[i][j] == '*')
//         return false;

//     Chequear si llegamos al final
//     if (lab->laberinto[i][j] == 'S')
//         return true;

//     Marcar la posición actual como visitada
//     char original = lab->laberinto[i][j];
//     lab->laberinto[i][j] = '*';

//     Intentar todas las cuatro direcciones
//     if (resolver_laberinto_aux(lab, i + 1, j) ){(
        
//         resolver_laberinto_aux(lab, i + 1, j)
//     }
    
    
//     || // abajo
//         resolver_laberinto_aux(lab, i - 1, j) || // arriba
//         resolver_laberinto_aux(lab, i, j + 1) || // derecha
//         resolver_laberinto_aux(lab, i, j - 1)) {
//         izquierda
//         return true;
//     }

//     Si no se encontró un camino, retroceder
//     lab->laberinto[i][j] = original;
//     return false;
// }
