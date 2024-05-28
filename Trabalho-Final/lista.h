#ifndef LISTA_H
#define LISTA_H

#include "jogodecartas.h"

typedef struct _cartas tCartas;

typedef struct _lista {
    tCartas carta;
    void *prox;
} tLista;

tLista *CriaLista();
tLista *CriaNoLista(tCartas cartaNova);
void InsereNoLista(tLista **lista, tLista *novoNo);
tCartas *RemovePosicaoLista(tLista **lista, int posicao);  
void MudaPosicaoLista(tLista **lista, int origem, int destino);
void LiberaLista(tLista **lista);
int TamanhoLista(tLista *lista);
void ImprimeLista(tLista *lista);

#endif