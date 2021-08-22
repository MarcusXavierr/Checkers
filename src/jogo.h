#ifndef JOGO_H
#define JOGO_H
#include "jogador.h"
#include "math.h"
void desenharTabuleiro(Jogador player1, Jogador player2);
int verifyIfIsDama(char tipo);
int calcularDistanciaMovimento(int l1, int c1, int l2, int c2);
void removerPeca(Jogador *jogador, int linha);
int comerComPecaComum(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2, int *pecas_comidas);
int comerComDama(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2, int *pecas_comidas);
void jogada(Jogador *jogador, Jogador *adversario, int *turno, char *nome_arquivo);
void salvarJogo(Jogador player1, Jogador player2, char *nome_arquivo, int turno);
void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador, Jogador *adversario, int turno, int *pecas_comidas, char *nome_arquivo);
int switchChar(char c);
void virarDama(Jogador *jogador, int l1, int c1);
void getInputDuringGame(const char *message, char* input, int turno, Jogador jogador, Jogador adversario, char *nome_arquivo);
int verifyIfDirectionIsRight(int l1, int l2, char type);
int verifyIfPieceExists(Jogador jogador, int l1, int c1, int *result, char *type);
int verifyIfUserWannaSave(char *input);
int calcularCoeficienteAngular(int y1, int x1, int y2, int x2);
#endif