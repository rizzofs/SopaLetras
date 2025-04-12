#include <stdio.h>
#include <stdbool.h>

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

void leerArchivo( const char *archivo, struct SopaDeLetras* sopa)
{
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
        fila++;
        columna = 0;
    }
    
    // Consiguiendo las palabras a buscar
    fscanf (f, "%c", &letra);
    while (!feof(f))
    {
        while (!feof(f) && letra !='\n') 
        {
            if (letra == '#'){ // Comentario a ignorar
                while (!feof(f) && letra != '\n'){
                    fscanf (f, "%c", &letra);
                }
            }
            if (letra != '\n'){
                printf("%c", letra);
                fscanf (f, "%c", &letra);
            }
            
        }
        printf("\n");
        fscanf (f, "%c", &letra);
    }

    fclose(f);
}


int main(){
    struct SopaDeLetras sopa;
    sopa.filas = 13;
    sopa.columnas = 16;
    leerArchivo("entrada.txt", &sopa);
    for (int i = 0; i < sopa.filas; i++){
        for (int j = 0; j < sopa.columnas; j++){
            printf("%c", sopa.grilla[i][j]);
        }
        printf("\n");
    }
    printf("\nLLEGA AL FINAL");
}
