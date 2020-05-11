#include "lector.h"
#include "ford_fulkerson.h"
#include "slist.h"

int main(int argc,  char **argv) {
  
  int cantidadVertices, flujoMaximo;
  int matrizInicial[MAX_VERTICES][MAX_VERTICES], matrizFinal[MAX_VERTICES][MAX_VERTICES]; //Matrices de adyacencia.
  char listaVertices[MAX_VERTICES][CHAR_MAX]; //Lista con los nombres de los vértices.
  char* archivoEntrada = malloc(sizeof(char) * CHAR_MAX);
  char* archivoSalida = malloc(sizeof(char) * CHAR_MAX);

  strcpy(archivoEntrada, argv[1]);
  strcpy(archivoSalida, argv[2]);

  cantidadVertices = lector_archivo(matrizInicial, matrizFinal, archivoEntrada, listaVertices);
  free(archivoEntrada);

  flujoMaximo = ford_fulkerson(matrizFinal, listaVertices, cantidadVertices);
  escritor_archivo(matrizInicial, matrizFinal, flujoMaximo, listaVertices, cantidadVertices, archivoSalida);
  free(archivoSalida);

  return 0;
}
