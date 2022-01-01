//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#ifndef MENU_H
#define MENU_H
#include <stdio.h>

#include "jogador.h"

void printMenu(Jogador *jogador1, Jogador *jogador2, int *rodada, char *nome_arquivo);
void getMenuInput(int *choice, const char *message);
void carregarJogo(Jogador *jogador1, Jogador *jogador2, char *nome_arquivo, int *rodada);
void readNameFromFile(Jogador *jogador, FILE *f, char *buffer, int bufferLength);
char *remove_white_spaces(char *str);

#endif