#include "lista.h"
#include "fila.h"
#include "jogodecartas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

tLista *CriaBaralho(tLista **lista){ 

  FILE *cartas; int j; tCartas temp;

  cartas = fopen("baralho1.dat", "r");

  for (j = 0; j < 52; j++) {
    fscanf(cartas, "%s %s %d %[^\n]s", temp.face, temp.naipe, &temp.valor, temp.nome);
    InsereNoLista(lista, CriaNoLista(temp));
  }
  fclose(cartas);

  return *lista;
}

void Embaralha(tLista **lista) {

  int sort_rand, i, tamanho = 52;
  tLista *baralhoaux = CriaLista(), *novoNo;
  tCartas *cartaDoBaralho;

  srand(time(NULL));

  for (i = 0; i < 52; i++) { 

      sort_rand = rand() % tamanho;
      cartaDoBaralho = RemovePosicaoLista(lista, sort_rand);
      novoNo = CriaNoLista(*cartaDoBaralho);
      InsereNoLista(&baralhoaux, novoNo);
      tamanho = tamanho - 1;
  }

  *lista = baralhoaux;
}

void EncherMao(tPilha *pilha, tLista **lista2) {
    int quantMao, cartasRestantes;
    tCartas *cartaDoBaralho;
    quantMao = TamanhoLista(*lista2);
    tLista *novoNo;

    if (quantMao < 5) {
        cartasRestantes = 5 - quantMao;

        while (TamanhoPilha(pilha) > 0 && cartasRestantes > 0) {
            cartaDoBaralho = PopNoPilha(pilha);
            novoNo = CriaNoLista(*cartaDoBaralho);
            InsereNoLista(lista2, novoNo);
            cartasRestantes = cartasRestantes - 1;
        }
    }
}

int mapeiaNaipe(const char *naipe) {
    if (strcmp(naipe, "♦") == 0)
        return 1;
    else if (strcmp(naipe, "♥") == 0)
        return 2;
    else if (strcmp(naipe, "♠") == 0)
        return 3;
    else if (strcmp(naipe, "♣") == 0)
        return 4;
    else
        return 0; 
}

int *Pontuacao(tLista **lista, int quantRemove, int pontuacoes[5], tPilha  *descarte) { // ORDEM DO VETOR: Ouros, copas, espadas, paus

  int i, j, k, cartasIguais = 0, cartasIguais2 = 0, tamanhoSeq = 1, contadorNaipes[4] ={0}, pares = 0, trincas = 0, quadras = 0, escolha, ouros1 = 0, copas1 = 0, espadas1 = 0, paus1 = 0;
  bool SeqCartas = false, MesmoNaipe = true;
  char naipe;
  tCartas *cartaTemp, cartasRemovidas[5];

  for (i = 0; i < quantRemove; i++) { //calcula o valor total das cartas
    cartaTemp = RemovePosicaoLista(lista, 0);
    PushNoPilha(descarte, CriaNoPilha(*cartaTemp));
    cartasRemovidas[i] = *cartaTemp;
    if (mapeiaNaipe(cartasRemovidas[i].naipe) == 1){
      pontuacoes[0] = pontuacoes[0] + cartasRemovidas[i].valor;
    }

    if (mapeiaNaipe(cartasRemovidas[i].naipe) == 2){
        pontuacoes[1] = pontuacoes[1] + cartasRemovidas[i].valor;
    }

    if (mapeiaNaipe(cartasRemovidas[i].naipe) == 3){
        pontuacoes[2] = pontuacoes[2] + cartasRemovidas[i].valor;
    }

    if (mapeiaNaipe(cartasRemovidas[i].naipe) == 4){
        pontuacoes[3] = pontuacoes[3] + cartasRemovidas[i].valor;
    }
  }

  for (i = 0; i < quantRemove; i++) { // Calcula naipes iguais
      naipe = mapeiaNaipe(cartasRemovidas[i].naipe);
      contadorNaipes[naipe - 1]++;
  }

  for (int i = 0; i < 4; i++) {
      if (contadorNaipes[i] > 1) {

          switch (i + 1) {
            case 1:
              printf("\n\033[38;2;50;205;50mVocê fez um BÔNUS DE NAIPES para OUROS: +(3 x %d) pontos!\033[0m\n", contadorNaipes[i]);
              pontuacoes[0] = pontuacoes[0] + contadorNaipes[i] * 3;
              break;
            case 2:
              printf("\n\033[38;2;50;205;50mVocê fez um BÔNUS DE NAIPES para COPAS: +(3 x %d) pontos!\033[0m\n", contadorNaipes[i]);
              pontuacoes[1] = pontuacoes[1] + contadorNaipes[i] * 3;
              break;
            case 3:
              printf("\n\033[38;2;50;205;50mVocê fez um BÔNUS DE NAIPES para ESPADAS: +(3 x %d) pontos!\033[0m\n", contadorNaipes[i]);
              pontuacoes[2] = pontuacoes[2] + contadorNaipes[i] * 3;
              break;
            case 4:
              printf("\n\033[38;2;50;205;50mVocê fez um BÔNUS DE NAIPES para PAUS: +(3 x %d) pontos!\033[0m\n", contadorNaipes[i]);
              pontuacoes[3] = pontuacoes[3] + contadorNaipes[i] * 3;
              break;
          }
      }
  }

  for (i = 0; i < quantRemove; i++) { // calcula sequencias
      int tamanhoSeqLocal = 1, ouros = 0, copas = 0, espadas = 0, paus = 0, bonus = 0;

      for (j = i; j < quantRemove - 1; j++) {
          if (cartasRemovidas[j].valor == cartasRemovidas[j + 1].valor - 1) {
              tamanhoSeqLocal += 1;
             if (mapeiaNaipe(cartasRemovidas[j].naipe) == 1|| mapeiaNaipe(cartasRemovidas[j + 1].naipe) == 1){
                ouros = ouros + 1;
              }
              if (mapeiaNaipe(cartasRemovidas[j].naipe) == 2|| mapeiaNaipe(cartasRemovidas[j + 1].naipe) == 2){
                copas = copas + 1;
              }
              if (mapeiaNaipe(cartasRemovidas[j].naipe) == 3|| mapeiaNaipe(cartasRemovidas[j + 1].naipe) == 3){
                espadas = espadas + 1;
              }
              if (mapeiaNaipe(cartasRemovidas[j].naipe) == 4|| mapeiaNaipe(cartasRemovidas[j + 1].naipe) == 4){
                paus = paus + 1;
              }

          } else {
              break;
          }
      }
    
      if (tamanhoSeqLocal >= 2) {
          bonus = bonus + (2 * tamanhoSeqLocal);
          printf("\n\033[38;2;50;205;50mVocê fez uma SEQUÊNCIA! +(2 x %d)\033[0m\n", tamanhoSeqLocal);

        if (ouros >= 1 && copas == 0 && espadas == 0 && paus == 0){
          pontuacoes[0] = pontuacoes[0] + bonus;
        } 
        if (ouros == 0 && copas >= 1 && espadas == 0 && paus == 0){
          pontuacoes[1] = pontuacoes[1] + bonus;
        } 
        if (ouros == 0 && copas == 0 && espadas >= 1 && paus == 0){
          pontuacoes[2] = pontuacoes[2] + bonus;
        }
        if (ouros == 0 && copas == 0 && espadas == 0 && paus >= 1){
          pontuacoes[3] = pontuacoes[3] + bonus;
        } 

        if (ouros >= 1 && copas >= 1 && espadas == 0 && paus == 0){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Copas\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros >= 1 && copas == 0 && espadas >= 1 && paus == 0){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Espadas\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros >= 1 && copas == 0 && espadas == 0 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros == 0 && copas >= 1 && espadas >= 1 && paus == 0){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Copas\n2- Espadas\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if(escolha == 2){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros == 0 && copas >= 1 && espadas == 0 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Copas\n2- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if(escolha == 2){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros == 0 && copas == 0 && espadas >= 1 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Espadas\n2- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
            if(escolha == 2){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 2);
        }

        if (ouros >= 1 && copas >= 1 && espadas >= 1 && paus == 0){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Copas\n3- Espadas\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if (escolha == 3){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
          }while(escolha < 1 || escolha > 3);
        }

        if (ouros >= 1 && copas >= 1 && espadas == 0 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Copas\n3- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if (escolha == 3){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 3);
        }

        if (ouros >= 1 && copas == 0 && espadas >= 1 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Espadas\n3- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
            if (escolha == 3){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 3);  
        }

        if (ouros == 0 && copas >= 1 && espadas >= 1 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Copas\n2- Espadas\n3- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if(escolha == 2){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
            if (escolha == 3){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 3);
        }

        if (ouros >= 1 && copas >= 1 && espadas >= 1 && paus >= 1){
          do{
            printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bonus da sequência em qual naipe?\n\n1- Ouros\n2- Copas\n3- Espadas\n\n4- Paus\n\n\033[0m");
            printf("Resposta: ");
            scanf("%d", &escolha);
            if (escolha == 1){
            pontuacoes[0] = pontuacoes[0] + bonus;
            }
            if(escolha == 2){
            pontuacoes[1] = pontuacoes[1] + bonus;
            }
            if (escolha == 3){
            pontuacoes[2] = pontuacoes[2] + bonus;
            }
            if (escolha == 4){
            pontuacoes[3] = pontuacoes[3] + bonus;
            }
          }while(escolha < 1 || escolha > 4);
        }

          i += tamanhoSeqLocal - 1;
      }
  }

  for (i = 1; i < quantRemove; i++) { //calcula pares, trincas e quadras
      if (cartasRemovidas[i].valor == cartasRemovidas[i - 1].valor) {
          cartasIguais++;

          if (cartasIguais == 1) {
              // Par
              pares++;
          } else if (cartasIguais == 2) {
              // Trinca
              pares--;
              trincas++;
          } else if (cartasIguais == 3) {
              // Quadra
              trincas--;
              quadras++;
          }
      } else {
          cartasIguais = 0;
      }
  } 

  for (j = 1; j < quantRemove; j++){    

    if (mapeiaNaipe(cartasRemovidas[j].naipe) == 1 || mapeiaNaipe(cartasRemovidas[j - 1].naipe) == 1){
    ouros1 = ouros1 + 1;
    }
    if (mapeiaNaipe(cartasRemovidas[j].naipe) == 2 || mapeiaNaipe(cartasRemovidas[j - 1].naipe) == 2){
    copas1 = copas1 + 1;
    }
    if (mapeiaNaipe(cartasRemovidas[j].naipe) == 3 || mapeiaNaipe(cartasRemovidas[j - 1].naipe) == 3){
    espadas1 = espadas1 + 1;
    }
    if (mapeiaNaipe(cartasRemovidas[j].naipe) == 4 || mapeiaNaipe(cartasRemovidas[j - 1].naipe) == 4){
    paus1 = paus1 + 1;
    }
  }

    if (quadras > 0) {

      if (ouros1 >= 1 && copas1 >= 1 && espadas1 >= 1 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez uma QUADRA!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus da QUADRA em qual naipe?\n\n1- Ouros\n2- Copas\n3- Espadas\n4- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 20;
        }
        if(escolha == 2){
        pontuacoes[1] = pontuacoes[1] + 20;
        }
        if (escolha == 3){
        pontuacoes[2] = pontuacoes[2] + 20;
        }
        if (escolha == 4){
        pontuacoes[3] = pontuacoes[3] + 20;
        }
        ouros1 = ouros1 - 1;
        copas1 = copas1 - 1;
        espadas1 = espadas1 - 1;
        paus1 = paus1 - 1;
        quadras = quadras - 1;

      }

    }

    if (trincas > 0) {

      if (ouros1 >= 1 && copas1 >= 1 && espadas1 >= 1 && paus1 == 0){
        printf("\n\033[38;2;50;205;50mVocê fez uma TRINCA!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus da TRINCA em qual naipe?\n\n1- Ouros\n2- Copas\n3- Espadas\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 5;
        }
        if(escolha == 2){
        pontuacoes[1] = pontuacoes[1] + 5;
        }
        if (escolha == 3){
        pontuacoes[2] = pontuacoes[2] + 5;
        }
        ouros1 = ouros1 - 1;
        copas1 = copas1 - 1;
        espadas1 = espadas1 - 1;
        trincas = trincas - 1;
      }

      if (ouros1 >= 1 && copas1 >= 1 && espadas1 == 0 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez uma TRINCA!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus da TRINCA em qual naipe?\n\n1- Ouros\n2- Copas\n3- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 5;
        }
        if(escolha == 2){
        pontuacoes[1] = pontuacoes[1] + 5;
        }
        if (escolha == 3){
        pontuacoes[3] = pontuacoes[3] + 5;
        }
        ouros1 = ouros1 - 1;
        copas1 = copas1 - 1;
        paus1 = paus1 - 1;
        trincas = trincas - 1;
      }

      if (ouros1 >= 1 && copas1 == 0 && espadas1 >= 1 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez uma TRINCA!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus da TRINCA em qual naipe?\n\n1- Ouros\n2- Espadas\n3- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 5;
        }
        if(escolha == 2){
        pontuacoes[2] = pontuacoes[2] + 5;
        }
        if (escolha == 3){
        pontuacoes[3] = pontuacoes[3] + 5;
        }
        ouros1 = ouros1 - 1;
        espadas1 = espadas1 - 1;
        paus1 = paus1 - 1;
        trincas = trincas - 1;
      }

      if (ouros1 == 0 && copas1 >= 1 && espadas1 >= 1 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez uma TRINCA!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus da TRINCA em qual naipe?\n\n1- Copas\n2- Espadas\n3- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[1] = pontuacoes[1] + 5;
        }
        if(escolha == 2){
        pontuacoes[2] = pontuacoes[2] + 5;
        }
        if (escolha == 3){
        pontuacoes[3] = pontuacoes[3] + 5;
        }
        copas1 = copas1 - 1;
        espadas1 = espadas1 - 1;
        paus1 = paus1 - 1;
        trincas = trincas - 1;
      } 
    }

    if (pares > 0) {

      if (ouros1 >= 1 && copas1 >= 1 && espadas1 == 0 && paus1 == 0){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Ouros\n2- Copas\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 2;
        }
        if(escolha == 2){
        pontuacoes[1] = pontuacoes[1] + 2;
        }
        ouros1 = ouros1 - 1;
        copas1 = copas1 - 1;
        pares = pares - 1;
      }

      if (ouros1 >= 1 && copas1 == 0 && espadas1 >= 1 && paus1 == 0){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Ouros\n2- Espadas\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 2;
        }
        if(escolha == 2){
        pontuacoes[2] = pontuacoes[2] + 2;
        }
        ouros1 = ouros1 - 1;
        espadas1 = espadas1 - 1;
        pares = pares - 1;
      }

      if (ouros1 >= 1 && copas1 == 0 && espadas1 == 0 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Ouros\n2- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[0] = pontuacoes[0] + 2;
        }
        if(escolha == 2){
        pontuacoes[3] = pontuacoes[3] + 2;
        }
        ouros1 = ouros1 - 1;
        paus1 = paus1 - 1;
        pares = pares - 1;
      }

      if (ouros1 == 0 && copas1 >= 1 && espadas1 >= 1 && paus1 == 0){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Copas\n2- Espadas\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[1] = pontuacoes[1] + 2;
        }
        if(escolha == 2){
        pontuacoes[2] = pontuacoes[2] + 2;
        }
        copas1 = copas1 - 1;
        espadas1 = espadas1 - 1;
        pares = pares - 1;
      }

      if (ouros1 == 0 && copas1 >= 1 && espadas1 == 0 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Copas\n2- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[1] = pontuacoes[1] + 2;
        }
        if(escolha == 2){
        pontuacoes[3] = pontuacoes[3] + 2;
        }
        copas1 = copas1 - 1;
        paus1 = paus1 - 1;
        pares = pares - 1;
      }

      if (ouros1 == 0 && copas1 == 0 && espadas1 >= 1 && paus1 >= 1){
        printf("\n\033[38;2;50;205;50mVocê fez um PAR!\033[0m\n");
        printf("\n\033[38;2;50;205;50mVocê deseja adicionar o bônus do PAR em qual naipe?\n\n1- Espadas\n2- Paus\n\n\033[0m");
        printf("Resposta: ");
        scanf("%d", &escolha);
        if (escolha == 1){
        pontuacoes[2] = pontuacoes[2] + 2;
        }
        if(escolha == 2){
        pontuacoes[3] = pontuacoes[3] + 2;
        }
        espadas1 = espadas1 - 1;
        paus1 = paus1 - 1;
        pares = pares - 1;
      }
    }

  return pontuacoes;
}

int PassaTurno(int TurnoAtual){

  TurnoAtual = TurnoAtual + 1;

  return TurnoAtual;
}

tFila TurnoTarefas(int turno, tFila *fila, int *prazoAux, int PontuacaoFalseTarefas[5]) {

  int aux, aux2;

  if(FilaVazia(fila) == 0){

    if(turno >= fila->prim->jogoTarefas.turno){
    
      if(prazoAux > 0){
        aux = fila->prim->jogoTarefas.turno + fila->prim->jogoTarefas.prazo;
        aux2 = aux - turno;
      
        if(aux <= turno){

          //parte que calcula: (Pn + Cn + En + On)
          
          PontuacaoFalseTarefas[0] = PontuacaoFalseTarefas[0] + fila->prim->jogoTarefas.recOuros; 
          PontuacaoFalseTarefas[1] = PontuacaoFalseTarefas[1] + fila->prim->jogoTarefas.recCopas;
          PontuacaoFalseTarefas[2] = PontuacaoFalseTarefas[2] + fila->prim->jogoTarefas.recEspadas;
          PontuacaoFalseTarefas[3] = PontuacaoFalseTarefas[3] + fila->prim->jogoTarefas.recPaus;

          RemoveNoFila(fila);
          *prazoAux = aux2;
        } 
      }
    }
  }
  return *fila;
}

void CompletaTarefa(tFila *fila, int pontuacoes[5], int PontuacaoTrueTarefas[5], int *prazoAtualizado){ 

  if (pontuacoes[0] >= fila->prim->jogoTarefas.recOuros && pontuacoes[1] >= fila->prim->jogoTarefas.recCopas && pontuacoes[2] >= fila->prim->jogoTarefas.recEspadas && pontuacoes[3] >= fila->prim->jogoTarefas.recPaus){
    pontuacoes[0] = pontuacoes[0] - fila->prim->jogoTarefas.recOuros;
    pontuacoes[1] = pontuacoes[1] - fila->prim->jogoTarefas.recCopas;
    pontuacoes[2] = pontuacoes[2] - fila->prim->jogoTarefas.recEspadas;
    pontuacoes[3] = pontuacoes[3] - fila->prim->jogoTarefas.recPaus;

    //PARTE QUE CALCULA: (At × (Pt + Ct + Et + Ot)
    PontuacaoTrueTarefas[0] = PontuacaoTrueTarefas[0] + (*prazoAtualizado * fila->prim->jogoTarefas.recOuros); 
    PontuacaoTrueTarefas[1] = PontuacaoTrueTarefas[1] + (*prazoAtualizado * fila->prim->jogoTarefas.recCopas);
    PontuacaoTrueTarefas[2] = PontuacaoTrueTarefas[2] + (*prazoAtualizado * fila->prim->jogoTarefas.recEspadas);
    PontuacaoTrueTarefas[3] = PontuacaoTrueTarefas[3] + (*prazoAtualizado * fila->prim->jogoTarefas.recPaus);

    if (fila->prim->jogoTarefas.premReembaralhamento != 0){
      pontuacoes[4] = pontuacoes[4] + fila->prim->jogoTarefas.premReembaralhamento;
    }
    
    printf("\n\033[38;2;50;205;50mVocê concluiu a tarefa!\033[0m\n");
    RemoveNoFila(fila);
    
  } else{
    printf("\n\033[1;31mVocê não tem pontuação suficiente para completar a tarefa!\033[0m\n");
  }
}

void ImprimeListaComCartas(tLista *lista) {
  tLista *atual = lista;

  if (atual != NULL) {

    while (atual != NULL) {
      printf(" ┌─────────┐");
      atual = atual->prox; 
    }
    printf("\n");
    atual = lista; 


    while (atual != NULL) {
      printf(" │ %-7s │", atual->carta.face);
      atual = atual->prox; 
    }
    printf("\n");  
    atual = lista; 

    while (atual != NULL) {
      printf(" │         │");
      atual = atual->prox;
    }
    printf("\n");  
    atual = lista; 

    while (atual != NULL) {
      printf(" │    %-4s   │", atual->carta.naipe);
      atual = atual->prox; 
    }
    printf("\n"); 
    atual = lista; 

    while (atual != NULL) {
      printf(" │         │");
      atual = atual->prox;
    }
    printf("\n");  
    atual = lista; 


    while (atual != NULL) {
      printf(" │ %7s │", atual->carta.face);
      atual = atual->prox; 
    }
    printf("\n");  
    atual = lista; 


    while (atual != NULL) {
      printf(" └─────────┘");
      atual = atual->prox; 
    }
    printf("\n");  
    atual = lista; 

  } else {
    printf("\nA lista está vazia.\n");
  }
}

tPilha ListaParaPilha(tPilha *pilha, tLista **lista){
  tCartas *aux;
  
  while (*lista != NULL){
    aux = RemovePosicaoLista(lista, 0);
    PushNoPilha(pilha, CriaNoPilha(*aux));
  }

  return *pilha;
}

void juntaTudo(tPilha *monte, tLista **mao, tPilha *descarte, tLista **listaAux){

  tCartas *aux, *aux2, *aux3;
  
  while (*mao != NULL){
    aux = RemovePosicaoLista(mao, 0);
    if (aux != NULL) {
      InsereNoLista(listaAux, CriaNoLista(*aux));
    }
  }

  while (!PilhaVazia(monte)){ 
    aux2 = PopNoPilha(monte);
    if (aux2 != NULL) {
      InsereNoLista(listaAux, CriaNoLista(*aux2));
    }
  }

  while (!PilhaVazia(descarte)){
    aux3 = PopNoPilha(descarte);
    if (aux3 != NULL) {
      InsereNoLista(listaAux, CriaNoLista(*aux3));
    }
  }

  Embaralha(listaAux);
  ListaParaPilha(monte, listaAux);
}

int CalcularPontuacaoFinal(int resultadoPontuacao[5], int PontuacaoTrueTarefas[5], int PontuacaoFalseTarefas[5]){

  int aux, aux2, aux3;

  //Essa parte calcula: (Pr + Cr + Er + Or)/2))
  aux = (resultadoPontuacao[0] + resultadoPontuacao[1] + resultadoPontuacao[2] + resultadoPontuacao[3])/2;
  //printf("\nEssa parte calcula: (Pr + Cr + Er + Or)/2)): %d", aux);
  //Essa parte faz a junção dos valores calculados em: (At × (Pt + Ct + Et + Ot)
  aux2 = PontuacaoTrueTarefas[0] + PontuacaoTrueTarefas[1] + PontuacaoTrueTarefas[2] + PontuacaoTrueTarefas[3];
  //printf("\n(At × (Pt + Ct + Et + Ot): %d", aux2);
  //Essa parte faz a junção dos valores calculados em: (At × (Pt + Ct + Et + Ot) + (Pr + Cr + Er + Or)/2))
  aux = aux + aux2;
  //printf("\nEssa parte faz a junção dos valores calculados em: (At × (Pt + Ct + Et + Ot) + (Pr + Cr + Er + Or)/2)): %d", aux);
  //Essa parte faz a junção dos valores calculados em: (Pn + Cn + En + On)
  aux3 = PontuacaoFalseTarefas[0] + PontuacaoFalseTarefas[1] + PontuacaoFalseTarefas[2] + PontuacaoFalseTarefas[3];
  //printf("\nEssa parte faz a junção dos valores calculados em: (Pn + Cn + En + On): %d", aux3);
  //Essa parte faz o final aux - aux3
  aux = aux - aux3;

  return aux;
}