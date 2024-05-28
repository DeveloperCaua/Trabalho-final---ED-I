#ifndef PILHA_H
#define PILHA_H

#include "jogodecartas.h"

typedef struct _cartas tCartas;

typedef struct _NoPilha {
    tCartas carta;
    void *prox;
} tNoPilha;

typedef struct _pilha{
  tNoPilha *topo;
} tPilha;

tPilha *CriaPilha();
tNoPilha *CriaNoPilha(tCartas cartaNova);
void PushNoPilha(tPilha *pilha, tNoPilha *NovoNo); //inserir
tCartas *PopNoPilha(tPilha *pilha); //remover
void liberaPilha(tPilha *pilha); 
int TamanhoPilha(tPilha *pilha);
void ImprimeTopoDaPilha(tPilha *pilha);
void ImprimePilha(tPilha *pilha); //função para teste (não utilizado em pilhas)
int PilhaVazia(tPilha *pilha);

#endif