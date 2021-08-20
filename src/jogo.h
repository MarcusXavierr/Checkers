#ifndef JOGO_H
#define JOGO_H
#include "jogador.h"
#include "math.h"
void desenharTabuleiro(Jogador player1, Jogador player2);
int calcularDistanciaMovimento(int l1, int c1, int l2, int c2);
void removerPeca(Jogador *jogador, int linha);
int verificarSeComeu(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2);
void jogada(Jogador *jogador, Jogador *adversario);

void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador, Jogador *adversario);
int switchChar(char c);
int verifyIfDirectionIsRight(int l1, int l2, char type);
int verifyIfPieceExists(Jogador jogador, int l1, int c1, int *result, char *type);
int verifyIfUserWannaSave(char *input);
#endif