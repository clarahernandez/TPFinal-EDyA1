#include "ford_fulkerson.h"

int min(int a, int b) {
  if(a <= b)
    return a;
  return b;
}

void actualizar_matriz(int matriz[][MAX_VERTICES], SList camino, int deltaFlujo) {
  SList nodo = camino;
  for( ; nodo != NULL; nodo = nodo->sig) {
    matriz[nodo->origen][nodo->destino] = matriz[nodo->origen][nodo->destino] - deltaFlujo;
    matriz[nodo->destino][nodo->origen] = matriz[nodo->destino][nodo->origen] + deltaFlujo;

  }
}

int encontrar_camino(int matriz[][MAX_VERTICES], int cantidadVertices) {
  SList camino = slist_crear();
  int encontreCamino = 0; //Bandera.
  int puedoSeguir = 1; //Bandera
  int sumidero = cantidadVertices-1;
  int f = 0;
  int c = 1;
  int deltaFlujo = INT_MAX;

  while (!encontreCamino && puedoSeguir) {
    while (c <= sumidero) {
      if (matriz[f][c] > 0 && !slist_buscar(camino, c)) {
        deltaFlujo = min(matriz[f][c], deltaFlujo);
        camino = slist_agregar_inicio(camino, f, c, deltaFlujo);

        if (c == sumidero ) {
          actualizar_matriz(matriz, camino, deltaFlujo);
          slist_destruir(camino);
          encontreCamino = 1;
          return 1;
        }
        f = c;
        c = 0;
      }
      c++;
    }
    if (f == 0 && c > sumidero) {
      puedoSeguir = 0;
      return 0;
    }
    if (c > sumidero) {
      f = camino->origen;
      c = camino->destino + 1;
      deltaFlujo = camino->deltaFlujo;
      camino = slist_eliminar_inicio(camino);
    }
  }
  slist_destruir(camino);
  return 0;

}

int ford_fulkerson(int matriz[][MAX_VERTICES], char listaVertices[][CHAR_MAX], int cantidadVertices) {

  int encontreCamino = 1; //bandera
  int flujoMaximo = 0;

  while(encontreCamino) {
    encontreCamino = encontrar_camino(matriz, cantidadVertices);
  }

  for(int i = 0; i < cantidadVertices; i++) {
    flujoMaximo = flujoMaximo + matriz[i][0];
  }

  return flujoMaximo;


}
