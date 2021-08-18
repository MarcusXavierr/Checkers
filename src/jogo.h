#ifndef JOGO_H
#define JOGO_H
#include "jogador.h"
void desenharTabuleiro(Jogador player1, Jogador player2);
void jogada(Jogador *jogador);
void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador);
int switchChar(char c);
int verifyIfPieceExists(Jogador *jogador, int l1, int c1, int *result, char *type);
#endif