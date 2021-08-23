//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include "jogador.h"
#include "jogo.h"
#include "utils/constants.h"
#include <stdio.h>
#include <string.h>
#include "utils/colors.h"
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

int validateInput(char *input, int *c1, int *c2, int *l1, int *l2, Jogador *jogador, Jogador *adversario, int *linha, char *tipo, int turno, char *nome_arquivo){
    char Cl1, Cl2;
    int tmp;
    char adversario_type[1];
    // gambiarra pra fazer a validação contra o adverário funcionar, sorry
    
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
    float coeficiente = calcularCoeficienteAngular(*l1, *c1, *l2, *c2);
    if(coeficiente != 1.0) return 0; // * validate
    int distancia = calcularDistanciaMovimento(*l1, *c1, *l2, *c2);
    int podeComer = verificarSePedraPodeComer(*jogador, *adversario, *l1, *c1);
    if(*tipo == 'x' || *tipo == 'o'){
        int ladoCerto = verifyIfDirectionIsRight(*l1, *l2, *tipo);
        if(!podeComer){
            if(!ladoCerto) return 0; //* validate
        }
        if(distancia > 2) return 0; //* validate
    }
    
    int soprou = pedraComumSoprou(distancia, podeComer, *l1, *c1, *l2, *c2, *adversario);
    if(soprou){
        return -1;
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

int verificarSePedraPodeComer(Jogador jogador, Jogador adversario, int l1, int c1){
    int tmp; char tmpc;
    int l, c, x, y, l2, c2;
    int pecaInimigaExiste = 0;
    int possibilidades[] = {1,1, 1,-1, -1,1, -1,-1};
    int possibilidades2[] = {2,2, 2,-2, -2,2, -2,-2};
    int espacoVazioInimigo, meuEspacoVazio;
    // TODO: verificar se existe uma peça inimiga em 
    //* (y+1, x+1),(y+1, x-1),(y-1, x+1),(y-1, x-1)
    for(y = 0, x = 1; y <= 6; y += 2, x += 2){
        l = possibilidades[y] + l1;
        c = possibilidades[x] + c1;
        if(l > 7 || c > 7 || c < 0 || l < 0) continue;
        pecaInimigaExiste = verifyIfPieceExists(adversario, l, c, &tmp, &tmpc);
        if(pecaInimigaExiste){
            l2 = possibilidades2[y] + l1;
            c2 = possibilidades2[x] + c1;
            if(l2 > 7 || c2 > 7 || c2 < 0 || l2 < 0) continue;
            espacoVazioInimigo = verifyIfPieceExists(adversario, l2, c2, &tmp, &tmpc);
            meuEspacoVazio = verifyIfPieceExists(jogador, l2, c2, &tmp, &tmpc);
            if(espacoVazioInimigo == 0 && meuEspacoVazio == 0) return 1;
        };
    }
    return 0;   
}

int pedraComumSoprou(int distancia, int podeComer, int l1, int c1, int l2, int c2, Jogador adversario){
    int xM, yM, tmp;
    char tmpc;
    xM = (c1 + c2) / 2;
    yM = (l1 + l2) / 2;
    if(podeComer == 1 && distancia == 1) return 1;
    if(podeComer == 1 && distancia == 2){
        int exists = verifyIfPieceExists(adversario, yM, xM, &tmp, &tmpc);
        if(exists == 0) return 1;
    }
    return 0;
}

char convertNumToChar(int num){
    if(num == 0) return 'H';
    if(num == 1) return 'G';
    if(num == 2) return 'F';
    if(num == 3) return 'E';
    if(num == 4) return 'D';
    if(num == 5) return 'C';
    if(num == 6) return 'B';
    if(num == 7) return 'A';

    return 'Z';
}