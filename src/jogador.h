//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[50];
    int **pecas; //* Aqui eu faço uma matriz com todas as posições de todas as peças do jogador
    char tipo_peca; //* C = clara, E = escura
} Jogador;

void getInputFromUser(const char *message, char* input);
void validateIfUserWantQuit(char *input);

#endif