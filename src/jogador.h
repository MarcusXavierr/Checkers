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

int validateInput(char *input, int *c1, int *c2, int *l1, int *l2, Jogador *jogador, Jogador *adversario, int *linha, char *tipo, int turno, char *nome_arquivo);
void getInputFromUser(const char *message, char* input);
void validateIfUserWannaQuit(char *input);
int **criaMatriz(int m, int n);
char convertNumToChar(int num);
int contarQtdDamas(Jogador jogador);
int verificarSePedraPodeComer(Jogador jogador, Jogador adversario, int l1, int c1);
int pedraComumSoprou(int distancia, int podeComer, int l1, int c1, int l2, int c2, Jogador adversario);
void preencherMatriz(int ***matriz, char tipo);

#endif