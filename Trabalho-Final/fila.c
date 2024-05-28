#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

tFila *CriaFila() {
  tFila *novo = malloc(sizeof(tFila));

  novo->prim = NULL;
  novo->ult = NULL;
  return novo;
}

tFila *CriaTarefas(tFila **fila) {

  FILE *tarefas;
  int j;
  tTarefas tarefasTemp;


  tarefas = fopen("tarefas.dat", "r");

  for (j = 0; j < 10; j++) {
    fscanf(tarefas, "%d %d %d %d %d %d %d ", &tarefasTemp.turno, &tarefasTemp.prazo, &tarefasTemp.recPaus, &tarefasTemp.recEspadas, &tarefasTemp.recOuros, &tarefasTemp.recCopas, &tarefasTemp.premReembaralhamento);
    InsereNoFila(*fila, CriaNoFila(tarefasTemp));
  }
  fclose(tarefas);

  return *fila;
}

tNoFila *CriaNoFila(tTarefas tarefas){
  
    tNoFila *novo = malloc(sizeof(tNoFila));

    novo->jogoTarefas.turno = tarefas.turno;
    novo->jogoTarefas.prazo = tarefas.prazo;
    novo->jogoTarefas.recPaus = tarefas.recPaus;
    novo->jogoTarefas.recEspadas = tarefas.recEspadas;
    novo->jogoTarefas.recOuros = tarefas.recOuros;
    novo->jogoTarefas.recCopas = tarefas.recCopas;
    novo->jogoTarefas.premReembaralhamento = tarefas.premReembaralhamento;
  
    novo->prox = NULL;

  return novo;
}

int FilaVazia(tFila *fila) {
  if (fila->prim == NULL && fila->ult == NULL){
    return 1;
  }else{
    return 0;
  }
}

void InsereNoFila(tFila *fila, tNoFila *NovoNo) {
  
  if (FilaVazia(fila)) {
    fila->prim = NovoNo;
    fila->ult = NovoNo;
  } else{
    fila->ult->prox = NovoNo;
    fila->ult = NovoNo;
  }
}

tNoFila *RemoveNoFila(tFila *fila) {

  tNoFila *aux;
  
  if (FilaVazia(fila)){
    return NULL;
  } else if (TamanhoFila(fila) == 1){
    aux = fila->prim;
    fila->prim = NULL;
    fila->ult = NULL;
    aux->prox = NULL;
  } else{
    aux = fila->prim;
    fila->prim = fila->prim->prox;
    aux->prox = NULL;
  }
  
return aux;
}

int TamanhoFila(tFila *fila) {
  
  int i = 1;
  
  tNoFila *auxprim = fila->prim, *auxult = fila->ult;
  if(FilaVazia(fila)){
    return 0;
  }else{
    if(fila->prim == fila->ult){
      return 1;
    }else{
      while(auxprim != auxult){
        auxprim = auxprim->prox;
        i++;
      }
      return i;
    }
  }
}

void ImprimeNoFila(tNoFila *fila, int *prazoAux) {

  printf("  \033[1;35mPrazo:\033[0m %d\n    (♣️: %d ♠️: %d \033[1;31m♦: %d ♥️: "
     "%d\033[0m)\n  \033[1;35mBonus\033[0m "
     "\033[1;35mde embaralhamento:\033[0m %d\n\n",
         *prazoAux, fila->jogoTarefas.recPaus,
         fila->jogoTarefas.recEspadas, fila->jogoTarefas.recOuros,
         fila->jogoTarefas.recCopas,
         fila->jogoTarefas.premReembaralhamento);
}

void LiberaFila(tFila *fila){
  
  tNoFila *aux;
  fila->ult = NULL;
  while (!FilaVazia(fila)) {
    aux = fila->prim->prox;
    free(fila->prim);
    fila->prim = aux;
  }
}