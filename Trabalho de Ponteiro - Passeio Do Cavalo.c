/***** Algoritmos e Programação 2 - 'Passeio do Cavalo' *****/

/********** Alunos:
 - Guilherme Antonio Garcia do Nascimento - 12311BSI304
 - Lais Silva Oliveira - 12121BSI260
 - Isabella Fernanda Cardoso Silva - 12411BSI357
**********/


/*Descrição:*/
/*Este código implementa o desafio do 'Passeio do Cavalo'. O jogo inicia um tabuleiro 4x4 em que o usuário escolhe o caminho até completar o desafio.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABULEIRO 4

// Usando função para imprimir o tabuleiro 4x4:
void imprimirTab(int tab[TABULEIRO][TABULEIRO]) {
  for(int i = 0; i < TABULEIRO; i++) {
    for(int j = 0; j < TABULEIRO; j++) {
      printf("%2d ", tab[i][j]);
    }
    printf("\n");
  }
}

// Usando função para verificar se as posições inseridas serão válidas:
int isSafe(int b, int c, int tab[TABULEIRO][TABULEIRO]) {
  return (b >= 0 && b < TABULEIRO && c >= 0 && c < TABULEIRO && tab[b][c] == -1);
}

// Usando uma função para os movimentos do cavalo.
void movimentosCavalo(int d, int e, int tab[TABULEIRO][TABULEIRO]) {
  printf("Possiveis movimentos do cavalo: \n");
  int movimentos[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
  for(int i = 0; i < 8; i++) {
    int prox_d = d + movimentos[i][0];
    int prox_e = e + movimentos[i][1];
    if(isSafe(prox_d, prox_e, tab)) {
      printf("Posicao %d: (Linha: %d, Coluna: %d)\n", i + 1, prox_d, prox_e);
    }
  }
}

//Usando uma função para iniciar o 'Passeio do Cavalo'.
void startTabuleiro(int tab[TABULEIRO][TABULEIRO], int **p) {
  //O tabuleiro será iniciado com -1.
  for(int i = 0; i < TABULEIRO; i++) {
    for(int j = 0; j < TABULEIRO; j++) {
      tab[i][j] = -1;
    }
  }
  //Gerando posição inicial aleatória para o cavalo.
  srand(time(0));
  int iniciarD = rand() % TABULEIRO;
  int iniciarE = rand() % TABULEIRO;

  //A posição inicial do cavalo será 0.
  tab[iniciarD][iniciarE] = 0;
  *p = &tab[iniciarD][iniciarE];

  printf("Posicao inicial do cavalo: Linha: %d, Coluna: %d\n", iniciarD, iniciarE);
  imprimirTab(tab);
}

//Usando uma função para verificar a situação do tabuleiro.
int situacaoTab(int tab[TABULEIRO][TABULEIRO]) {
  for (int i = 0; i < TABULEIRO; i++) {
    for(int j = 0; j < TABULEIRO; j++) {
      if(tab[i][j] == -1) {
        return 0;
      }
    }
  }
  return 1;
}

//Usando uma função para verificar se o cavalo pode se mover.
int restCavalo(int d, int e, int tab[TABULEIRO][TABULEIRO]) {
  int movimentos[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
  for(int i = 0; i < 8; i++) {
    int testa_d = d + movimentos[i][0];
    int testa_e = e + movimentos[i][1];
    if(isSafe(testa_d, testa_e, tab)) {
      return 1;
    }
  }
  return 0;
}

int main() {
  int tblr[TABULEIRO][TABULEIRO];
  int movimento, *p;

  startTabuleiro(tblr, &p);

  int d = (p - &tblr[0][0]) / TABULEIRO;
  int e = (p - &tblr[0][0]) % TABULEIRO;


//Estrutura do jogo:
  while(1) {
    //O menu com a movimentação do cavalo começa aqui:
    movimentosCavalo(d, e, tblr);
    printf("Insira a movimentacao do cavalo entre 1 - 8 ou insira 0 para sair: ");
    scanf("%d", &movimento);

    if(movimento == 0) { //Verifica se o usuário que continuar, ou finalizar o jogo.
      printf("Jogo encerrado pelo usuario.\n");
      break;
    }

    //Possíveis movimentos do cavalo:
    int movimentos[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    int prox_d = d + movimentos[movimento - 1][0];
    int prox_e = e + movimentos[movimento - 1][1];

    if(isSafe(prox_d, prox_e, tblr)) {
      //Atualiza a posição do cavalo no tabuleiro:
      tblr[prox_d][prox_e] = tblr[d][e] + 1;
      d = prox_d;
      e = prox_e;
      imprimirTab(tblr);
    } else {
      printf("Movimento invalido. Tente novamente!\n");
    }
    if(!restCavalo(d, e, tblr)) {
      if(situacaoTab(tblr)) {
        printf("Parabens! Voce completou o tabuleiro, voce venceu!\n");
        break;
      } else {
        printf("Nao existem mais movimentos possiveis. Infelizmente, Voce perdeu!\n");
        break;
      }
    }
  }
  return 0;
}