# Trabajo práctico integrador

## Año: 2025

## Integrantes:
*   Valentín Giaccone
*   Gonzalo Ibañez
*   Federico Rizzo
---
## Docentes:
* Pablo Chale
* Mariano Goldman
---

## Funciones: 
```c
void leerArchivo(const char *archivo, struct SopaDeLetras *sopa)
```
Esta función lee un archivo de texto que contine una sopa de letras y palabras a buscar. Dentro del mismo realizamos las siguientes tareas: 
1) Abre el archivo, y verifica que no tenga errores. 
2) Lee los caracteres fila por fila hasta un salto de linea ``` \n``` y almacena cada letra en una matriz llamada grilla, a su vez actualiza la cantidad de filas y columnas.
3) Identifica palabras en el archivo cuya linea no comienze con ```#```. Luego almacena las palabras en un arreglo dentro de ```SopaDeLetras```, junto a su longitud.
4) Una vez finalizada la lectura cierra el archivo con ``fclose()``