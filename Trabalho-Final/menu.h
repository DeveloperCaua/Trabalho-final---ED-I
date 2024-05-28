#ifndef MENU_H
#define MENU_H

#include "lista.h"

void exibirMenu(int turno, tLista *mao, int resultadoPontuacao[5], tPilha *baralho, tFila *tarefas, int prazoAux, int *prazoAtualizado);
void MenuFimDeJogo(int PontuacaoFinal);
int obterEscolha();

#endif