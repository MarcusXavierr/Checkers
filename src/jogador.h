//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[50];
    int qtd_pecas;
    int **pecas; //* Aqui eu faço uma matriz com todas as posições de todas as peças do jogador
    char tipo_peca; //* C = clara, E = escura
} Jogador;

void getInputFromUser(const char *message, char* input);
void validateIfUserWannaQuit(char *input);
int **criaMatriz(int m, int n);
void preencherMatriz(int ***matriz, char tipo);

#endif