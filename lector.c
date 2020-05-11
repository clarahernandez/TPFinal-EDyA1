#include "lector.h"

char* lector_fuente_sumidero(FILE* fentrada, char buffer[CHAR_MAX]) {
  int i;  //Variable auxiliar.
  char c; //Variable auxiliar.

  while((c = fgetc(fentrada)) != '\n'); //Ignora la linea de "Fuente"/"Sumidero".

  for(i = 0;(c=fgetc(fentrada)) != '\n'; i++){
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return buffer;
}

int lector_puntos_intermedios(FILE* fentrada, char listaVertices[][CHAR_MAX]) {
  char c;  //Variable auxiliar.
  int i; //Variable auxiliar.
  int numVertice = 1; //Empieza en 1 ya que está la fuente.
  char buffer[CHAR_MAX]; //Donde se guardarán los nombres de los vértices.

  while((c = fgetc(fentrada)) != '\n'); //Ignora la linea de puntos intermedios.

  for(i = 0; (c = fgetc(fentrada)) != '\n'; i = 0, numVertice++) {
    buffer[i] = c;
    i++;
    while((c = fgetc(fentrada)) != ',' && c != '\n') {
        buffer[i]=c;
        i++;
    }
    if (c == '\n') break;
    buffer[i] = '\0';
    strcpy(listaVertices[numVertice], buffer);
  }
  buffer[i] = '\0';
  strcpy(listaVertices[numVertice], buffer);
  return numVertice + 2;
}

int posicion(char lista[][CHAR_MAX], char nombre[CHAR_MAX], int cantidadVertices) {
  int i; //Variable auxiliar.

  for (i = 0 ; i < cantidadVertices  ; i++) {
    if (strcmp(nombre, lista[i]) == 0) break;
  }

  if (i >= cantidadVertices) return -1; //En caso de que el vértice no esté en la lista.
  return i;
}

void lector_conexiones(FILE* fentrada, int matrizInicial[][MAX_VERTICES], int matrizFinal[][MAX_VERTICES], char listaVertices[][CHAR_MAX], int cantidadVertices) {
  int fila, columna, i; //Variables auxiliares.
  char c; //Variable auxiliar.
  char buffer[CHAR_MAX]; //Donde se guardan los nombres de los vértices y el peso.

  while((c = fgetc(fentrada)) != '\n'); //Salteamos "Conexiones".

  for(i = 0 ; (c = fgetc(fentrada)) != EOF; i = 0) {
    buffer[i] = c;
    i++;
    while((c = fgetc(fentrada)) != ',') {
      buffer[i] = c;
      i++;
    }
    buffer[i] = '\0';
    fila = posicion(listaVertices, buffer, cantidadVertices);
    i = 0;
    while((c = fgetc(fentrada)) != ',' ) {
      buffer[i] = c;
      i++;
    }
    buffer[i] = '\0';
    columna = posicion(listaVertices, buffer, cantidadVertices);
    i = 0;
    while((c = fgetc(fentrada)) != '\n' ) {
      buffer[i] = c;
      i++;
    }
    buffer[i] = '\0';
    matrizInicial[fila][columna] = atoi(buffer);
    matrizFinal[fila][columna] = atoi(buffer);
  }
}

void inicializar_matrices(int matrizInicial[][MAX_VERTICES], int matrizFinal[][MAX_VERTICES], int cantidadVertices) {
  int f, c; //Variables auxiliares.
  for (f = 0; f < cantidadVertices; f++) {
    for (c = 0; c < cantidadVertices; c++) {
      matrizInicial[f][c] = 0;
      matrizFinal[f][c] = 0;
    }
  }
}

int lector_archivo(int matrizInicial[][MAX_VERTICES], int matrizFinal[][MAX_VERTICES], char* entrada, char listaVertices[][CHAR_MAX]) {

  FILE* fentrada;
  char buffer[CHAR_MAX];
  char sumidero[CHAR_MAX];
  int cantidadVertices;

  fentrada = fopen(entrada, "r");

  assert(fentrada != NULL && "No se puede abrir el archivo de entrada.\n");

  strcpy(listaVertices[0],lector_fuente_sumidero(fentrada, buffer)); //Copiamos la fuente.
  strcpy(sumidero, lector_fuente_sumidero(fentrada, buffer)); //Copiamos el sumidero.
  cantidadVertices = lector_puntos_intermedios(fentrada, listaVertices); //Obtenemos los puntos intermedios.
  strcpy(listaVertices[cantidadVertices-1], sumidero); //Copiamos el sumidero en la última posición.
  inicializar_matrices(matrizInicial, matrizFinal, cantidadVertices); //Inicializamos las matrices con todos 0.
  lector_conexiones(fentrada, matrizInicial, matrizFinal, listaVertices, cantidadVertices); //Leemos las aristas con sus pesos.

  return cantidadVertices;
}

void escritor_archivo(int matrizInicial[][MAX_VERTICES], int matrizFinal[][MAX_VERTICES], int flujoMaximo, char listaVertices[][CHAR_MAX], int cantidadVertices, char* salida) {
  int f,c;  //Variables auxiliares.
  int flujoInicial;
  FILE* fsalida;

  fsalida = fopen(salida, "w");

  assert(fsalida != NULL && "No se puede abrir el archivo de salida.\n");

  fprintf(fsalida, "Flujo máximo\n%d\nFlujos\n", flujoMaximo);

  for(f = 0; f < cantidadVertices ; f++) {
    for (c = 0; c < cantidadVertices; c++) {
      flujoInicial = matrizInicial[f][c];
      if (flujoInicial > 0) {
        fprintf(fsalida,"%s,%s,%d,%d\n", listaVertices[f], listaVertices[c], flujoInicial, matrizFinal[c][f]);
      }
    }
  }
  fclose(fsalida);
 printf("El archivo de salida ha sido creado con éxito.\n");
}
