// Borrar de la estructura sopa el char de palabras
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define TAMANIO_MAXIMO_GRILLA 100
#define TAMANIO_MAXIMO_PALABRA 50
#define MAXIMO_PALABRAS 100

// Colores ANSI
#define ROJO "\033[1;31m"
#define BLANCO "\033[0m"

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
    char palabras[MAXIMO_PALABRAS][TAMANIO_MAXIMO_PALABRA]; //Lista de palabras
    int cantidad_palabras;
    int longitud[MAXIMO_PALABRAS]; //agregue esto
    struct ResultadoPalabra datos[MAXIMO_PALABRAS];
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
        
        for (int i = 0; i < sopa->cantidad_palabras; i++){            
            strcpy(sopa->datos[i].palabra, sopa->palabras[i]);
            sopa->datos[i].encontrada = false;
        }
        
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
        if (sopa->datos[i].encontrada){
            printf("Palabra: %s, Encontrada\n", sopa->datos[i].palabra);
        } else {
            printf("Palabra: %s, Sin encontrar\n", sopa->datos[i].palabra);
        }
    }
}

//Funcion para colorear las palabras una a una.
void colorearPalabras(struct SopaDeLetras *sopa, struct ResultadoPalabra  *palabra){
    if (palabra->encontrada){
        unsigned int filaInicio = palabra->inicio.fila;
        unsigned int ColumnaInicio = palabra->inicio.columna;
        unsigned int filaFin = palabra->fin.fila;
        unsigned int ColumnaFin = palabra->fin.columna;

        //Vertical Arriba
        if (ColumnaInicio == ColumnaFin && filaInicio > filaFin){
            for(int x = filaInicio; x >= filaFin; x--){
                printf(ROJO "%c " BLANCO, sopa->grilla[x][ColumnaInicio]);    
            }
        }
        //Diagonal Derecha Arriba
        else if(filaInicio < filaFin && ColumnaInicio < ColumnaFin){
            for (int x = filaInicio; x <= filaFin; x++){
                for (int y = ColumnaInicio; y <= ColumnaFin; y++){
                    printf(ROJO "%c " BLANCO, sopa->grilla[x][y]);            
                }
            }
        }  
        //Horizontal Derecha
        else if (filaInicio == filaFin && ColumnaInicio <= ColumnaFin){
            for(int y = ColumnaInicio; y <= ColumnaFin; y++ )
            printf(ROJO "%c " BLANCO, sopa->grilla[filaInicio][y]);
        }
        //Diagonal Derecha Abajo
        else if(filaInicio > filaFin && ColumnaInicio < ColumnaFin){
            for (int x = filaInicio; x >= filaFin; x--){
                for (int y = ColumnaInicio; y <= ColumnaFin; y++){
                    printf(ROJO "%c " BLANCO, sopa->grilla[x][y]);            
                }
            }
        }
        //Vertical Abajo
        else if(ColumnaInicio == ColumnaFin && filaInicio < filaFin){
            for(int x = filaInicio; x <= filaFin; x++ ){
                printf(ROJO "%c " BLANCO, sopa->grilla[x][ColumnaInicio]);
            }
        }
        //Diagonal Izquierda Abajo
        else if(filaInicio > filaFin && ColumnaInicio > ColumnaFin){
            for(int x = filaInicio; x >= filaFin;x++){
                for(int y = ColumnaInicio; y >= ColumnaFin; y--){
                    printf(ROJO "%c " BLANCO, sopa->grilla[x][y]);
                }
            }
        }
        //Horizontal Izquierda
        else if(filaInicio == filaFin && ColumnaInicio >= ColumnaFin){
            for(int y = ColumnaInicio; y <= ColumnaFin; y--){
                printf(ROJO "%c " BLANCO, sopa->grilla[filaInicio][y]);
            }
            
        }
        //Diagonal Izquierda Arriba
        else if(filaInicio < filaFin && ColumnaInicio > ColumnaFin){
            for(int x = filaInicio; x <= filaFin; x++){
                for(int y = ColumnaInicio; y >= ColumnaFin; y--){
                    printf(ROJO "%c " BLANCO, sopa->grilla[x][y]);
                }
            }
        }
        
    }
}

//Funcion recursiva para colorear todas las palabras (Hacer)
void colorearTodasLasPalabras(struct SopaDeLetras *sopa){
    
}

//Función recursiva para encontrar la palabra.
bool buscarPalabra(struct SopaDeLetras *sopa, int filaSopa, int columnaSopa, char palabra[TAMANIO_MAXIMO_PALABRA], int columnaPalabra, int direccion){
    char letraPalabra = palabra[columnaPalabra];
    char letraSopa = sopa->grilla[filaSopa][columnaSopa];

    
    //   printf("Palabra: %s, letra: %c, letraSopa: %c, direccion: %d, coordenadas (%d, %d)\n", palabra, letraPalabra, letraSopa, direccion, filaSopa, columnaSopa);
    
    
    //  Caso Base: Llego al final de la cadena de la palabra que buscaba
    if (letraPalabra == '\0'){
        // palabraEncontrada();
        return true;
    }
    // if (columnaPalabra > strlen(palabra) - 1){
    //     printf("Encontro la palabra %s", palabra);
    //     return true;
    // }

    //  Caso Base: Chequear límites
    if (filaSopa < 0 || columnaSopa < 0 || columnaSopa >= sopa->columnas|| filaSopa >= sopa->filas)
        return false;

    // Comprobar si la letra de la palabra es igual a la letra que tiene la sopa
    if (letraPalabra == letraSopa) {
        if (direccion == 0){
            return (
                buscarPalabra(sopa, filaSopa-1, columnaSopa, palabra, columnaPalabra+1, 1)|| //Vertical Arriba
                buscarPalabra(sopa, filaSopa-1, columnaSopa+1, palabra, columnaPalabra+1, 2)|| // Diagonal Derecha Arriba
                buscarPalabra(sopa, filaSopa, columnaSopa+1, palabra, columnaPalabra+1, 3)|| // Horizontal Derecha
                buscarPalabra(sopa, filaSopa+1, columnaSopa+1, palabra, columnaPalabra+1, 4)|| // Diagonal Derecha Abajo
                buscarPalabra(sopa, filaSopa+1, columnaSopa, palabra, columnaPalabra+1, 5)|| //Vertical Abajo
                buscarPalabra(sopa, filaSopa+1, columnaSopa-1, palabra, columnaPalabra+1, 6)|| //Diagonal Izquierda Abajo
                buscarPalabra(sopa, filaSopa, columnaSopa-1, palabra, columnaPalabra+1, 7)|| //Horizontal Izquierda
                buscarPalabra(sopa, filaSopa-1, columnaSopa-1, palabra, columnaPalabra+1, 8) // Diagonal Izquierda Arriba
            );
        } else {
            switch (direccion) 
            {
            case 1: // Vertical Arriba
                return buscarPalabra(sopa, filaSopa-1, columnaSopa, palabra, columnaPalabra+1, 1);
                break;
            case 2:// Diagonal Derecha Arriba
                return buscarPalabra(sopa, filaSopa-1, columnaSopa+1, palabra, columnaPalabra+1, 2);
                break;
            case 3:// Horizontal Derecha
                return buscarPalabra(sopa, filaSopa, columnaSopa+1, palabra, columnaPalabra+1, 3);
                break;
            case 4: // Diagonal Derecha Abajo
                return buscarPalabra(sopa, filaSopa+1, columnaSopa+1, palabra, columnaPalabra+1, 4);
                break;
            case 5://Vertical Abajo
                return buscarPalabra(sopa, filaSopa+1, columnaSopa, palabra, columnaPalabra+1, 5);
                break;
            case 6://Diagonal Izquierda Abajo
                return buscarPalabra(sopa, filaSopa+1, columnaSopa-1, palabra, columnaPalabra+1, 6);
                break;
            case 7://Horizontal Izquierda
                return buscarPalabra(sopa, filaSopa, columnaSopa-1, palabra, columnaPalabra+1, 7);
                break;
            case 8:// Diagonal Izquierda Arriba
                return buscarPalabra(sopa, filaSopa-1, columnaSopa-1, palabra, columnaPalabra+1, 8);
                break;
            
            default:
                break;
            }
        }
    } else {
        return false;
    }
}

void recorrerSopa(struct SopaDeLetras *sopa){
    
    for (int i = 0; i < sopa->filas; i++){
        for (int j = 0; j < sopa->columnas; j++){
           // for (int k = 0; k < sopa->cantidad_palabras; k++){
            for (int k = 0; k < sopa->cantidad_palabras; k++){
             //   printf("La palabra %s esta en el estado %d\n", sopa->datos[k].palabra, sopa->datos[k].encontrada); 
                if (!sopa->datos[k].encontrada){
                //    printf("Como no esta encontrada, sopa grilla == palabra, %c == %c\n", sopa->grilla[i][j], sopa->datos[k].palabra[0]);
                  //  printf("Coordenadas: %d, %d\n", i, j);
                    // if (sopa->grilla[i][j] == sopa->datos[k].palabra[0]){
                    //     sopa->datos[k].encontrada = buscarPalabra(sopa, i, j, sopa->datos[k].palabra, 0, 0);
                    // //    printf("Termina la recursividad, el resultado fue:\n", sopa->datos[k].encontrada);
                    if (sopa->grilla[i][j] == sopa->palabras[k][0]){
                        
                        // sopa->datos[k].encontrada = buscarPalabra(sopa, i, j, sopa->datos[k].palabra, 0, 0);
                        sopa->datos[k].encontrada = buscarPalabra(sopa, i, j, sopa->palabras[k], 0, 0);
                    //    printf("Termina la recursividad, el resultado fue:\n", sopa->datos[k].encontrada);
                    }
                }
            }
        }
    }
}

//Función para generar el archivo de salida. (Hacer)  

int main() {
    struct SopaDeLetras sopa;
    sopa.filas = 0;
    sopa.columnas = 0;
    sopa.cantidad_palabras = 0;
    struct ResultadoPalabra palabraDatos[MAXIMO_PALABRAS];
    

    leerArchivo("entrada.txt", &sopa);

    int opcion;

    do {
        printf("*****************************\n");
        printf("************MENU***************\n");
        printf("*******************************\n");
        printf("1 - Mostrar sopa de letras\n");
        printf("2 - Mostrar Palabras\n");
        printf("3 - Resolver\n");
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
                recorrerSopa(&sopa);
                break;
            case 4:
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
