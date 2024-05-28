#ifndef FILA_H
#define FILA_H

typedef struct _tarefas{
  int turno;
  int prazo;
  int recPaus;
  int recEspadas;
  int recOuros;
  int recCopas;
  int premReembaralhamento;
} tTarefas;

typedef struct _NoFila{
  tTarefas jogoTarefas;
  void *prox;
} tNoFila;

typedef struct _fila {
    tNoFila *prim;
    tNoFila *ult;
} tFila;

tFila *CriaFila();  
tFila *CriaTarefas(tFila **fila); 
tNoFila *CriaNoFila(tTarefas jogoTarefas);
void InsereNoFila(tFila *fila, tNoFila *NovoNo);
tNoFila *RemoveNoFila(tFila *fila); 
int TamanhoFila(tFila *fila); 
void ImprimeNoFila(tNoFila *fila, int *prazoAux);  
int FilaVazia(tFila *fila);
void LiberaFila(tFila *fila); 

#endif