#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
};

void leerArchivo( const char *archivo, struct SopaDeLetras* sopa){
    int fila = 0;
    int columna = 0;
    char letra;
    FILE *f = fopen(archivo, "r");
    if (f == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Armando la sopa de letra
    fscanf (f, "%c", &letra);
    while (!feof(f) && letra !='\n')
    {
        while (!feof(f) && letra !='\n') 
        {
            sopa->grilla[fila][columna]=letra;
            columna++;
            fscanf (f, "%c", &letra);
        }
        fscanf (f, "%c", &letra);
        sopa->columnas = columna; //Almaceno la cantidad de columnas
        fila++;
        columna = 0;
    }
    sopa->filas=fila; //Almaceno la cantidad de filas
    
    
    // Consiguiendo las palabras a buscar
    fscanf (f, "%c", &letra); 
    while (!feof(f))
    {
        char palabra[TAMANIO_MAXIMO_PALABRA];
        int indice = 0;
        
        while (!feof(f) && letra !='\n') 
        {
            if (letra == '#'){ // Comentario a ignorar, lineas que inician con #
                while (!feof(f) && letra != '\n'){
                    fscanf (f, "%c", &letra);
                }
            }
            if (letra != '\n'){
                //printf("%c", letra);
                palabra[indice] = letra;
                indice++;
                fscanf (f, "%c", &letra);
                
            }
            
        }
        palabra[indice] = '\0';
        if (sopa->cantidad_palabras < MAXIMO_PALABRAS) {
            strcpy(sopa->palabras[sopa->cantidad_palabras], palabra); //Agrego las palabras en el vector. 
            sopa->cantidad_palabras++;
        }
        
        fscanf (f, "%c", &letra);
    }

    fclose(f);
} 

void imprimirMatriz(struct SopaDeLetras* sopa){
    printf("Sopa de letra \n");
    for (int i = 0; i < sopa->filas; i++){
        for (int j = 0; j < sopa->columnas; j++){
            printf("%c", sopa->grilla[i][j]);
        }
        printf("\n");
    };

}
//Imprime correctamente la matriz.

void imprimirPalabras(struct SopaDeLetras* sopa) {
    printf("Vector de palabras almacenadas:\n");
    for (int i = 0; i < sopa->cantidad_palabras; i++) {
        printf("Palabra %d: %s\n", i + 1, sopa->palabras[i]);
    }
}
//Hay que arreglar, que imprime lineas vacias dentro del vector de palabras.



int main(){
    struct SopaDeLetras sopa;
    sopa.filas = 13;
    sopa.columnas = 16;
    leerArchivo("entrada.txt", &sopa);
    imprimirMatriz(&sopa);
    printf("***************************\n");
    imprimirPalabras(&sopa);

    return 0;
}
