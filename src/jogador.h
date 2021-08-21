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

int validateInput(char *message, char *input, int *c1, int *c2, int *l1, int *l2, Jogador *jogador, Jogador *adversario, int *linha, char *tipo, int turno);
void getInputFromUser(const char *message, char* input);
void validateIfUserWannaQuit(char *input);
int **criaMatriz(int m, int n);
int contarQtdDamas(Jogador jogador);
void preencherMatriz(int ***matriz, char tipo);

#endif