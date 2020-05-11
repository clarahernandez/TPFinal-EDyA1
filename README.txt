PARA COMPILAR:

Primero ejecutamos en la consola la
siguiente linea:

--------------------------------------------------------------------------
$ gcc -std=c99 -Wall -c main.c slist.c ford_fulkerson.c lector.c -o main
--------------------------------------------------------------------------

Creandonos main en la misma carpeta.

Ejecutamos la siguiente linea donde "archivoEntrada" es el archivo donde se
encuentra la información de entrada y "archivoSalida" es archivo donde nos
mostrará la solución. Estos archivos deben estar en la misma carpeta donde
se vaya a ejecutar el programa.

--------------------------------------------------------------------------
$ ./main archivoEntrada archivoSalida
--------------------------------------------------------------------------

SOBRE EL CÓDIGO:
Para resolver el "Problema de flujo máximo" dada una red, utilicé el algoritmo
de Ford-Fulkerson.
 Para representar el grafo uso una matriz de adyacencia. Las filas representan
los vértices de origen y las columnas representan los vértices de llegada.
 Uso un grafo residual, para poder así redistribuir el flujo. Es
decir que cada posición de la matriz indica cuanto flujo puedo distribuir, ya
sea el que puedo mandar o el que ya mandé.
 El programa contempla hasta 1000 vértices, definido en una constante global en
los archivos "lector.h" y "ford_fulkerson.h". En caso de querer probar con más
vértices habría que cambiar los valores en ambos archivos.

FUENTE:
https://es.wikipedia.org/wiki/Algoritmo_de_Ford-Fulkerson-
