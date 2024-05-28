#ifndef JOGODECARTAS_H 
#define JOGODECARTAS_H

typedef struct _cartas {
    char face[3];
    char naipe[2];
    int valor;
    char nome[20];
} tCartas;

#include "lista.h"
#include "fila.h"
#include "pilha.h"

typedef struct _lista tLista;
typedef struct _pilha tPilha;

tLista *CriaBaralho();
void Embaralha(tLista **lista);
tLista *MaoInicial(tLista **baralho, tLista **mao);
int *Pontuacao(tLista **mao, int quantRemove, int pontuacoes[5], tPilha *descarte);
void EncherMao(tPilha *lista, tLista **lista2);
int PassaTurno(int TurnoAtual);
tFila TurnoTarefas(int turno, tFila *fila, int *prazoAux, int PontuacaoFalseTarefas[5]);
void CompletaTarefa(tFila *fila, int pontuacoes[5], int PontuacaoTrueTarefas[5], int *prazoAtualizado);
void ImprimeListaComCartas(tLista *lista);
tPilha ListaParaPilha(tPilha *pilha, tLista **lista);
void juntaTudo(tPilha *monte, tLista **mao, tPilha *descarte, tLista **listaAux);
int CalcularPontuacaoFinal(int resultadoPontuacao[5], int PontuacaoTrueTarefas[5], int PontuacaoFalseTarefas[5]);

#endif