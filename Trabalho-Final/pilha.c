#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tPilha *CriaPilha(){
  tPilha *novo = malloc(sizeof(tPilha));

  novo->topo = NULL;
  return novo;
}

tNoPilha *CriaNoPilha(tCartas cartaNova){
  tNoPilha *novoNo = malloc(sizeof(tNoPilha));

  strcpy(novoNo->carta.face, cartaNova.face);
  strcpy(novoNo->carta.naipe, cartaNova.naipe);
  novoNo->carta.valor = cartaNova.valor;
  strcpy(novoNo->carta.nome, cartaNova.nome);
  
  novoNo->prox = NULL;

  return novoNo;
}

int PilhaVazia(tPilha *pilha){
  if (pilha->topo == NULL){
    return 1;
  }
  else{
    return 0;
  }
}

void PushNoPilha(tPilha *pilha, tNoPilha *NovoNo){
  tNoPilha *aux;
  
  if(PilhaVazia(pilha)){
    pilha->topo = NovoNo;
  } else{
    aux = pilha->topo;
    pilha->topo = NovoNo;
    pilha->topo->prox = aux;
  }
}

int TamanhoPilha(tPilha *pilha){

  int tamanho = 0;
  tNoPilha *aux = pilha->topo;

  if(PilhaVazia(pilha)){
    return 0;
  } else{

    while(aux != NULL){
      aux = aux->prox;
      tamanho++;
    }
  }
  return tamanho;
}

tCartas *PopNoPilha(tPilha *pilha){
    tNoPilha *aux;
    tCartas *cartaRemovida;

  if(PilhaVazia(pilha)){
    return NULL;
  }

  if(TamanhoPilha(pilha) == 1){
    aux = pilha->topo;
    pilha->topo = NULL;
    aux->prox = NULL; //boa prática a se fazer
    cartaRemovida = &aux->carta;
  } else{

    aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    cartaRemovida = &aux->carta;
    aux->prox = NULL;
  }

  return cartaRemovida;
}

void liberaPilha(tPilha *pilha){
    tNoPilha *aux;
  
    while (!PilhaVazia(pilha)) {
      aux = pilha->topo->prox;
      free(pilha->topo);
      pilha->topo = aux;
    }
}
  
void ImprimeTopoDaPilha(tPilha *pilha){

  printf("\nTopo da pilha: %s %s %d %s\n", pilha->topo->carta.face, pilha->topo->carta.naipe, pilha->topo->carta.valor, pilha->topo->carta.nome);

}

void ImprimePilha(tPilha *pilha){
  tNoPilha *aux;  
  aux = pilha->topo;
  
  while(aux != NULL){
    printf("%s %s %d %s\n", aux->carta.face, aux->carta.naipe, aux->carta.valor, aux->carta.nome);
    aux = aux->prox;
  }
}