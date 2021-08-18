//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include "jogador.h"
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
    int matrizx[12][3] = {0,0,'x',0,2,'x',0,4,'x',0,6,'x',
                          1,1,'x',1,3,'x',1,5,'x',1,7,'x',
                          2,0,'x',2,2,'x',2,4,'x',2,6,'x'};

    int matrizo[12][3] = {5,1,'o',5,3,'o',5,5,'o',5,7,'o',
                          6,0,'o',6,2,'o',6,4,'o',6,6,'o',
                          7,1,'o',7,3,'o',7,5,'o',7,7,'o'};
                
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

