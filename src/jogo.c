#include "utils/colors.h"
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>

void desenharTabuleiro(Jogador player1, Jogador player2)
{
    char matriz[8][8];
    int x, y;
    for (int i = 0; i < 8; i++) for (int j = 0; j <8; j++) matriz[i][j] = ' ';
    for(int linha = 0; linha < player1.qtd_pecas; linha ++){
        x = player1.pecas[linha][0]; 
        y = player1.pecas[linha][1];
        matriz[x][y] = player1.pecas[linha][2];
    }
    for(int linha = 0; linha < player2.qtd_pecas; linha ++){
        matriz[player2.pecas[linha][0]][player2.pecas[linha][1]] = player2.pecas[linha][2];
    }

    printf("   1  2  3  4  5  6  7  8\n");
    for(int i = 0, c = 'H'; i < 8; i++, c--)
    {
        printf("%c ", c);
        for(int j = 0; j < 8; j++)
        {
            if(i % 2 == 0){
                if(j % 2 == 0){
                    printf(BG_WHITE(BLACK(" %c ")), matriz[i][j]);
                }
                else{
                    printf(BG_BLACK(" %c "), matriz[i][j]);
                }
            }
            else{
                if(j % 2 != 0){
                    printf(BG_WHITE(BLACK(" %c ")), matriz[i][j]);
                }
                else{
                    printf(BG_BLACK(" %c "), matriz[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void jogada(Jogador *jogador)
{
    char message[50], input[50];
    char Cl1, Cl2;
    int c1, c2, l1, l2, linha;
    int pieceExists = 0;
    char tipo;
    sprintf(message, "%s, é a sua vez: ", jogador->nome);
    lerJogada(message, input, &c1, &c2, &l1, &l2, &linha, &tipo, jogador);
    // TODO: Verificar se o user está indo para trás, ou para frente
    jogador->pecas[linha][0] = l2;
    jogador->pecas[linha][1] = c2;
    
}

int switchChar(char c) {
    if(c == 'h' || c == 'H') return 0;
    if(c == 'g' || c == 'G') return 1;
    if(c == 'f' || c == 'F') return 2;
    if(c == 'e' || c == 'E') return 3;
    if(c == 'd' || c == 'D') return 4;
    if(c == 'c' || c == 'C') return 5;
    if(c == 'b' || c == 'B') return 6;
    if(c == 'a' || c == 'A') return 7;
    return -1;

}

void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador)
{   
    int is_valid = 0, qtd_input;
    char Cl1, Cl2;
    getInputFromUser(message, input);
    qtd_input = sscanf(input,"%c%d %c%d", &Cl1, c1, &Cl2, c2);
    while(qtd_input != 4){
        inputError:
        printf("Por favor, insira um input válido\n");
        getInputFromUser(message, input);
        qtd_input = sscanf(input,"%c%d %c%d", &Cl1, c1, &Cl2, c2);
    }
    *l1 = switchChar(Cl1);
    *l2 = switchChar(Cl2);
    *c1 = *c1 - 1; *c2 = *c2 - 1;
    if(*l1 < 0 || *l2 < 0 || *c1 < 0 || *c2 < 0 || *c1 > 7 || *c2 > 7) goto inputError;
    int exists = verifyIfPieceExists(jogador, *l1, *c1, linha, tipo);
    if(!exists) goto inputError;
    // verifyIfDirectionIsRight()
    
}

int verifyIfDirectionIsRight(int c1, int l1, int c2, int l2, char type)
{
    if(type == 'o')
    {
        if(c1 > c2) return 1;
        else return 0;
    }
    if(type == 'x')
    {
        if(c1 < c2) return 1;
        else return 0;
    }

    if(type == 'X' || type == 'O')
    {
        return 1;
    }
}

int verifyIfPieceExists(Jogador *jogador, int l1, int c1, int *result, char *type){
    for(int linha = 0; linha < jogador->qtd_pecas; linha++){
        int linhaIgual = jogador->pecas[linha][0] == l1;
        int colunaIgual = jogador->pecas[linha][1] == c1;
        if(linhaIgual && colunaIgual){
            *type = jogador->pecas[linha][2];
            *result = linha;
            return 1;
        }
    }
    return 0;
}