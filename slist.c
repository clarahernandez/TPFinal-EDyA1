#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_inicio(SList lista, int origen, int destino, int deltaFlujo) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->origen = origen;
  nuevoNodo->destino = destino;
  nuevoNodo->deltaFlujo = deltaFlujo;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

int slist_buscar(SList lista, int vertice) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    if (nodo->destino == vertice){
      return 1;
    }
    }

  return 0;
}

SList slist_eliminar_inicio(SList lista) {
  SList listaAux = lista->sig;
  free(lista);
  return listaAux;
}
