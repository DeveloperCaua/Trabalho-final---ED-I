// GRUPO: Cauã Enrico Beling (mátricula: 202200212), Marcos Aurélio () e Gabriel
// dos Santos Souza (mátricula: 202220217).

#include "fila.h"
#include "jogodecartas.h"
#include "lista.h"
#include "menu.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  int op, op2, PosAtual, PosDest, QuantRemocao, turno = 1, prazoAtualizado, PontuacaoFinal;
  static int resultadoPontuacao[5] = {0}, PontuacaoTrueTarefas[5] = {0},
             PontuacaoFalseTarefas[5] = {0};
  tLista *mao = CriaLista(), *baralhoAux = CriaLista();
  tFila *tarefas = CriaFila();
  tPilha *descarteDeCartas = CriaPilha(), *monteDeCartas = CriaPilha();

  CriaTarefas(&tarefas);
  int prazoAux = tarefas->prim->jogoTarefas.prazo;
  CriaBaralho(&baralhoAux);
  Embaralha(&baralhoAux);
  ListaParaPilha(monteDeCartas, &baralhoAux);
  EncherMao(monteDeCartas, &mao);

  do {
    exibirMenu(turno, mao, resultadoPontuacao, monteDeCartas, tarefas, prazoAux,
               &prazoAtualizado);

    printf("\n\n");  
    op = obterEscolha();

    switch (op) {

    case 1:

      if (mao == NULL) {
        printf("\n\033[1;31m  Você não tem cartas na mão para "
               "reposicionar!\033[0m\n\n");
        break;
      }

      printf(
          "\n  Qual posição deseja mudar? (informe a posição de origem)\n\n");
      printf("\033[1;32m╔════════\033[0m ♧ \033[1;32m══════\033[0m "
             "\033[1;31m♡\033[0m \033[1;32m═══════\033[0m \033[1;35mMão\033[0m "
             "\033[1;32m══════\033[0m \033[1;31m♢\033[0m "
             "\033[1;32m══════\033[0m ♤ \033[1;32m═════════╗\033[0m\n");

      printf("");
      ImprimeListaComCartas(mao);

      printf("\033[1;"
             "32m╚═══════════════════════════════════════════════════════════╝"
             "\033[0m\n");

      printf("\033[1;32m  Resposta:\033[0m ");
      scanf("%d", &PosAtual);
      if (PosAtual > TamanhoLista(mao) || PosAtual < 1) {
        printf("\n\033[1;31m  Você digitou uma posição não existente na "
               "mão!\033[0m\n");
        break;
      }
      printf("\n  Qual a posição de destino?\n\n\033[1;32m  Resposta:\033[0m ");
      scanf("%d", &PosDest);
      if (PosDest > TamanhoLista(mao) || PosDest < 1) {
        printf("\n\033[1;31m  Você digitou uma posição não existente na "
               "mão!\033[0m\n");
        break;
      }
      printf("\n");

      PosAtual =
          PosAtual -
          1; // o pos ta sempre 1 adiantado, encontrei essa solução provisória
      MudaPosicaoLista(&mao, PosAtual, PosDest);

      break;

    case 2:

      if (mao == NULL) {
        printf(
            "\n\033[1;31mVocê não tem cartas na mão para descartar!\033[0m\n");
        break;
      }
      printf(
          "\n\n\033[1;31mATENÇÃO!\033[0m Para que a pontuação dos bônus seja "
          "feita da maneira correta, siga os seguintes passos:\n\n1- Faça o "
          "descarte de uma \033[1;31mSEQUÊNCIA\033[0m POR VEZ e EM ORDEM!. "
          "Exemplo: 1, 2, 3...\033[0m;\n\n2- Ao fazer descarte de "
          "\033[1;31mPARES\033[0m, \033[1;31mTRINCAS\033[0m ou "
          "\033[1;31mQUADRAS\033[0m, organize as cartas uma do lado da outra "
          "assim como as \033[1;31mSEQUÊNCIAS\033[0m!\n\n3- NÃO FAÇA O "
          "DESCARTE DE MAIS DE UM \033[1;31mPAR\033[0m/\033[1;31mTRINCA\033[0m "
          "e/ou \033[1;31mQUADRA!!\033[0m. Sempre faça o descarte de "
          "\033[1;31mPARES\033[0m, \033[1;31mTRINCAS\033[0m ou "
          "\033[1;31mQUADRAS\033[0m de maneira separada!! \n4- Não faça o "
          "descarte de uma \033[1;31mSEQUÊNCIA\033[0m juntamente com um "
          "\033[1;31mPAR\033[0m/\033[1;31mTRINCA\033[0m e/ou "
          "\033[1;31mQUADRA!!\033[0m\n\nDeseja prosseguir?\n\n1- Sim\n2- "
          "Não\n\nResposta: ");

      scanf("%d", &op2);
      switch (op2) {
      case 1:
        printf("\nQuantas cartas você deseja descartar?\nResposta: ");
        scanf("%d", &QuantRemocao);

        if (QuantRemocao > TamanhoLista(mao) || QuantRemocao < 1) {
          printf("\n\033[1;31mVocê não possui essa quantidade de "
                 "cartas!\033[0m\n");
          break;
        }

        printf("\n");
        Pontuacao(&mao, QuantRemocao, resultadoPontuacao, descarteDeCartas);

        break;

      case 2:
        break;

      default:
        printf("\n\033[1;31mOpção inválida. Tente novamente.\033[0m\n");
      }

      break;

    case 3:
      if (FilaVazia(tarefas)){
        printf("\n\033[1;31mAs missões acabaram! Este é o último turno antes do fim do jogo!\033[0m\n");
        break;
      }
      if (tarefas == NULL) {
        printf("\nNão há uma tarefa vigente!\n");
      } else {
        CompletaTarefa(tarefas, resultadoPontuacao, PontuacaoTrueTarefas,
                       &prazoAtualizado);
        TurnoTarefas(turno, tarefas, &prazoAux, PontuacaoFalseTarefas);
      }
      break;

    case 4:

      if (resultadoPontuacao[4] == 0) {
        printf("\n\033[1;31mVocê não tem bonus de reembaralhamento no "
               "momento!\033[0m\n");
      } else {
        juntaTudo(monteDeCartas, &mao, descarteDeCartas, &baralhoAux);
        EncherMao(monteDeCartas, &mao);
        resultadoPontuacao[4]--;
      }

      break;

    case 5:

      if (PilhaVazia(monteDeCartas)) {
        juntaTudo(monteDeCartas, &mao, descarteDeCartas, &baralhoAux);
        EncherMao(monteDeCartas, &mao);
      }

      turno = PassaTurno(turno);
      *tarefas = TurnoTarefas(turno, tarefas, &prazoAux, PontuacaoFalseTarefas);
      EncherMao(monteDeCartas, &mao);

      if (FilaVazia(tarefas)) {
        PontuacaoFinal = CalcularPontuacaoFinal(resultadoPontuacao, PontuacaoTrueTarefas, PontuacaoFalseTarefas);
        MenuFimDeJogo(PontuacaoFinal);
        op = 6;
      }

      break;

    case 6:
      LiberaLista(&baralhoAux), LiberaLista(&mao), LiberaFila(tarefas), liberaPilha(descarteDeCartas), liberaPilha(monteDeCartas);
      printf("\n\033[38;2;0;255;0mSaindo...\033[0m\n");

      break;

    default:
      printf("\n\033[1;31mOpção inválida!\033[0m\n");
      break;
    }
  } while (op != 6);

  return 0;
}