#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tLista *CriaLista() {
  tLista *lista = NULL;

  return lista;
}

tLista *CriaNoLista(tCartas cartaNova) {
  tLista *novo = malloc(sizeof(tLista));

  strcpy(novo->carta.face, cartaNova.face);   //parâmetros (destino, origem)
  strcpy(novo->carta.naipe, cartaNova.naipe);
  novo->carta.valor = cartaNova.valor;
  strcpy(novo->carta.nome, cartaNova.nome);
  
  novo->prox = NULL;

  return novo;
}

void InsereNoLista(tLista **lista, tLista *novoNo) {
  tLista *aux, **aux2;

  aux2 = lista;
  while ((*aux2) != NULL) {
    aux2 = (tLista **)&((*aux2)->prox);
  }
  aux = novoNo;
  aux->prox = (*aux2);
  (*aux2) = aux;
}

void ImprimeLista(tLista *lista) {
    tLista *atual = lista;

    while (atual != NULL) {
        printf(" (%-2s %s %-2d %-17s)\n", atual->carta.face, atual->carta.naipe, atual->carta.valor, atual->carta.nome);
        atual = atual->prox;
    }
}

tCartas *RemovePosicaoLista(tLista **lista, int pos) {
  int i;
  tLista *aux, *aux2;
  tCartas *cartaRetirada;

  aux = (*lista);

  if (pos == 0) { 
    (*lista) = aux->prox;
    aux->prox = NULL;
    cartaRetirada = &(aux->carta);  
    return cartaRetirada;
  } else {
    for (i = 0; i < pos - 1; i++)
      aux = aux->prox;
    aux2 = aux->prox;
    aux->prox = aux2->prox;
    aux2->prox = NULL;
    cartaRetirada = &(aux2->carta);  
    return cartaRetirada;
  }
}

void InsereNoPosLista(tLista **lista, tLista *novoNo, int pos) {
  int i = 1;
  tLista *aux, **aux2;

  aux2 = lista;
  while (i < pos && (*aux2) != NULL) {
    aux2 = (tLista **)&((*aux2)->prox);
    i++;
  }
  aux = novoNo;
  aux->prox = (*aux2);
  (*aux2) = aux;
}

int TamanhoLista(tLista *lista) {
  int tamanho = 0;
  tLista *atual = lista; 

  while (atual != NULL) {
    tamanho++;
    atual = atual->prox;
  }

  return tamanho;
}

void MudaPosicaoLista(tLista **lista, int posOrig, int posDest) {
  tCartas *aux = RemovePosicaoLista(lista, posOrig);
  InsereNoPosLista(lista, CriaNoLista(*aux), posDest);
}

int ListaVazia(tLista *lista) {
  if (lista == NULL)
    return 1;
  else
    return 0;
}

void LiberaLista(tLista **lista) {
  tLista *aux;
  while (!ListaVazia(*lista)) {
    aux = (*lista)->prox;
    free(*lista);
    (*lista) = aux;
  }
}

