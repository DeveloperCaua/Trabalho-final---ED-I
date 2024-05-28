#include <stdio.h>
#include "menu.h"
#include "lista.h"
#include "jogodecartas.h"
#include "pilha.h"

void exibirMenu(int turno, tLista *mao, int resultadoPontuacao[5], tPilha *baralho, tFila *tarefas, int prazoAux, int *prazoAtualizado) {
  printf("\n\033[1;32m╔═══════\033[0m ♧ \033[1;32m══════\033[0m \033[1;31m♡\033[0m \033[1;32m══════\033[0m \033[1;34;40m MENU \033[0m \033[1;32m══════\033[0m \033[1;31m♢\033[0m \033[1;32m══════\033[0m ♤ \033[1;32m════════╗\033[0m\n");

  printf("\n  \033[1;35mMonte:\033[0m  🃏 %2d \n", TamanhoPilha(baralho));

  
  printf("\n  \033[1;35mPontuações:\033[0m\033[1;31m%3d ♦   %3d ♥\033[0m   %3d ♠   %3d ♣    *%3d \n", resultadoPontuacao[0], resultadoPontuacao[1], resultadoPontuacao[2], resultadoPontuacao[3], resultadoPontuacao[4]);

  printf("\n");
  
  if(FilaVazia(tarefas) == 0){
    if(tarefas->prim->jogoTarefas.turno <= turno){
    
      int aux = tarefas->prim->jogoTarefas.turno + tarefas->prim->jogoTarefas.prazo;
      int aux2 = aux - turno;
      prazoAux = aux2; 
      *prazoAtualizado = prazoAux;

      if(prazoAux != 0){
        ImprimeNoFila(tarefas->prim, &prazoAux);
      }
    }
  }
  
    if (mao != NULL) {
       
  printf("\n  \033[1;35mTurno:\033[0m \033[1;33m%d\033[0m                  \n", turno);
       
  printf("\n  \033[1;35mMão:\033[0m                                                  \n");

  printf("\n"); ImprimeListaComCartas(mao);

        

  printf("\033[1;32m╔═══════════════════════════════════════════════════════════╗\033[0m\n");
    }

    printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m  \033[1;32m1 -\033[0m \033[1;36mReposicionar cartas da mão.      \033[0m                    \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m  \033[1;32m2 -\033[0m \033[1;36mDescartar cartas.      \033[0m                              \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m  \033[1;32m3 -\033[0m \033[1;36mCumprir tarefa.      \033[0m                                \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m  \033[1;32m4 -\033[0m \033[1;36mReembaralhar tudo. (*:%d)        \033[0m                     \033[1;32m║\033[0m\n", resultadoPontuacao[4]);
    printf("\033[1;32m║\033[0m  \033[1;32m5 -\033[0m \033[1;36mFinalizar turno.      \033[0m                               \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m  \033[1;32m6 -\033[0m \033[1;31mSair.      \033[0m                                          \033[1;32m║\033[0m\n");
    printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
    printf("\033[1;32m╚═══════════════════════════════════════════════════════════╝\033[0m\n\n");
    printf("  \033[1;36mDigite a opção desejada\033[0m\n\033[1;32m  Resposta:\033[0m");
}

void MenuFimDeJogo(int PontuacaoFinal){
   printf("\n\033[1;32m╔═══════\033[0m ♧ \033[1;32m══════\033[0m \033[1;31m♡\033[0m \033[1;32m══════\033[0m \033[1;34;40m MENU \033[0m \033[1;32m══════\033[0m \033[1;31m♢\033[0m \033[1;32m══════\033[0m ♤ \033[1;32m════════╗\033[0m\n");
   printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
   printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
   printf("\033[1;32m║\033[0m                  \033[1;35mPontuação Final:\033[0m   %2d 🎉                \033[1;32m║\033[0m\n",PontuacaoFinal);
   printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
   printf("\033[1;32m║\033[0m                                                           \033[1;32m║\033[0m\n");
printf("\033[1;32m╚═══════════════════════════════════════════════════════════╝\033[0m\n\n");
}

int obterEscolha() {
    int op;
    scanf("%d", &op);
    while (getchar() != '\n');
    return op;
}
