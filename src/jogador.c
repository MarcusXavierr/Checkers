//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include "jogador.h"
#include "jogo.h"
#include "utils/constants.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void getInputFromUser(const char *message, char* input)
{
    printf("%s", message);
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = '\0';
    validateIfUserWannaQuit(input);
}

void validateIfUserWannaQuit(char *input)
{
    int result = strcmp(input, "sair");
    if(result == 0)
    {
        printf("Tchau!\n");
        exit(0);
    }
}

void preencherMatriz(int ***matriz, char tipo)
{
    int linhas = 12;
    int itens = 3;
    int matrizx[12][3] = {0,1,'x',0,3,'x',0,5,'x',0,7,'x',
                          1,0,'x',1,2,'x',1,4,'x',1,6,'x',
                          2,1,'x',2,3,'x',2,5,'x',2,7,'x'};

    int matrizo[12][3] = {5,0,'o',5,2,'o',5,4,'o',5,6,'o',
                          6,1,'o',6,3,'o',6,5,'o',6,7,'o',
                          7,0,'o',7,2,'o',7,4,'o',7,6,'o'};
                
    int **C = criaMatriz(linhas,itens);
    if(tipo == 'x'){
        for(int linha = 0; linha < linhas; linha++){
            for(int col = 0; col < itens; col++) C[linha][col] = matrizx[linha][col];
        }
    }
    else{
        for(int linha = 0; linha < linhas; linha++){
            for(int col = 0; col < itens; col++) C[linha][col] = matrizo[linha][col];
        }
    }
    *matriz = C;
}

int **criaMatriz(int m, int n)
{
    int **matriz;
    matriz = malloc(m * sizeof(int*));
    // Aloca as matrizes
    for(int linha = 0; linha < m; linha++)
    {
        matriz[linha] = malloc(n * sizeof(int));
        if(matriz[linha] == NULL){
            printf("Não existe memória suficiente");
            return NULL;
        }
    }
    return matriz;
}

int validateInput(char *message, char *input, int *c1, int *c2, int *l1, int *l2, Jogador *jogador, Jogador *adversario, int *linha, char *tipo, int turno){
    char Cl1, Cl2;
    int tmp;
    char adversario_type[1];
    // gambiarra pra fazer a validação contra o adverário funcionar, sorry
    getInputDuringGame(message, input, turno, *jogador, *adversario);
    int qtd_input = sscanf(input,"%c%d %c%d", &Cl1, c1, &Cl2, c2);
    if(qtd_input != 4) return 0; //* validate
    *l1 = switchChar(Cl1);
    *l2 = switchChar(Cl2);
    *c1 = *c1 - 1; *c2 = *c2 - 1;
    if(*l1 < 0 || *l2 < 0 || *c1 < 0 || *c2 < 0 || *c1 > 7 || *c2 > 7) return 0; //* validate
    if(*c1 == *c2) return 0; //* validate
    int exists = verifyIfPieceExists(*jogador, *l1, *c1, linha, tipo);
    int espacoOcupado = verifyIfPieceExists(*adversario, *l2, *c2, &tmp, adversario_type);
    int espacoOcupadoPorMim = verifyIfPieceExists(*jogador, *l2, *c2, &tmp,adversario_type);
    if(!exists || espacoOcupado || espacoOcupadoPorMim) return 0; // * validate
    int distancia = calcularDistanciaMovimento(*l1, *c1, *l2, *c2);
    if(*tipo == 'x' || *tipo == 'o'){
        int ladoCerto = verifyIfDirectionIsRight(*l1, *l2, *tipo);
        if(!ladoCerto) return 0; //* validate
        if(distancia > 2) return 0; //* validate
    }

    return 1;
}


int contarQtdDamas(Jogador jogador){
    int count = 0;
    for(int linha = 0; linha < jogador.qtd_pecas; linha ++){
        if(jogador.pecas[linha][2] == 'X' || jogador.pecas[linha][2] == 'O') count++;
    }
    return count;
}