#include "utils/colors.h"
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            if(i % 2 != 0){
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

void jogada(Jogador *jogador, Jogador *adversario)
{
    char message[50], input[50];
    int c1, c2, l1, l2, linha;
    int pieceExists = 0;
    char *tipo = malloc(sizeof(char));
    *tipo = '\0';
    sprintf(message, "%s, é a sua vez: ", jogador->nome);
    lerJogada(message, input, &c1, &c2, &l1, &l2, &linha, tipo, jogador, adversario);
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

void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador, Jogador *adversario)
{   
    int is_valid = 0, qtd_input;
    int result;
    do{
        result = validateInput(message, input, c1, c2,l1,l2, jogador, adversario, linha, tipo);
        int isDama = verifyIfIsDama(*tipo);
        if(isDama == -1) result = 0;
        if(isDama == 0){
            if(calcularDistanciaMovimento(*l1, *c1, *l2, *c2) == 2){
                result = comerComPecaComum(jogador, adversario, *l1, *c1, *l2, *c2);
            }
        }
        else if(isDama == 1){
            result = comerComDama(jogador, adversario, *l1, *c1, *l2, *c2);
        }

        if(result == 0) printf(BOLD("\nInput inválido, tente novamente\n"));
    }while(result == 0);
    free(tipo);
    
    
}

int verifyIfIsDama(char tipo)
{
    if(tipo == 'x' || tipo == 'o')
        return 0;

    if(tipo == 'X' || tipo ==  'O')
        return 1;
    
    return -1;
}

int comerComDama(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2)
{
    int result, localizacao;
    int qtd = 0;
    char tipo;
    if(l1 < l2){
        if(c1 < c2){
            for(int y = l1, x = 1; y < l2; y++, c1++){
                result = verifyIfPieceExists(*adversario, y, c1, &localizacao, &tipo);
                if(result) qtd++;
            }
        }else{
            for(int y = l1, x = 1; y < l2; y++, c1--){
                result = verifyIfPieceExists(*adversario, y, c1, &localizacao, &tipo);
                if(result) qtd++;
            }
        }
        
    }else{
        if(c1 < c2){
            for(int y = l2; y < l1; y++, c2--){
                result = verifyIfPieceExists(*adversario, y,c2, &localizacao, &tipo);
                if(result) qtd++;
            }
        }else{
            for(int y = l2; y < l1; y++, c2++){
                result = verifyIfPieceExists(*adversario, y, c2, &localizacao, &tipo);
                if(result) qtd++;
            }
        }
    }
    
    if(qtd > 1) return 0;
    if(qtd == 1){
        removerPeca(adversario, localizacao);
    }
    return 1;
}



void removerPeca(Jogador *jogador, int linha){
    
    for(; linha < (jogador->qtd_pecas - 1); linha++ ){
        jogador->pecas[linha][0] = jogador->pecas[linha + 1][0];
        jogador->pecas[linha][1] = jogador->pecas[linha + 1][1];
        jogador->pecas[linha][2] = jogador->pecas[linha + 1][2];
    }
    free(jogador->pecas[linha]);
    jogador->qtd_pecas--;
}
int comerComPecaComum(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2){
    int xM, yM, localizacao_peca;
    char tipo;
    xM = (c1 + c2) / 2;
    yM = (l1 + l2) / 2;
    int exists = verifyIfPieceExists(*adversario,yM, xM, &localizacao_peca, &tipo);
    if(exists){
        removerPeca(adversario, localizacao_peca);
        return 1;
    }
    return 0;
}   
int calcularDistanciaMovimento(int l1, int c1, int l2, int c2){
    int distancia, x, y;
    x = pow((c1 - c2), 2); 
    y = pow((l1 - l2), 2); 
    distancia = sqrt((x + y));
    return distancia;
}

int verifyIfDirectionIsRight(int l1, int l2, char type)
{
    if(type == 'o')
    {
        if(l1 > l2) return 1;
        else return 0;
    }
    if(type == 'x')
    {
        if(l1 < l2) return 1;
        else return 0;
    }

    if(type == 'X' || type == 'O')
    {
        return 1;
    }
}

int verifyIfPieceExists(Jogador jogador, int l1, int c1, int *result, char *type){
    for(int linha = 0; linha < jogador.qtd_pecas; linha++){
        int linhaIgual = jogador.pecas[linha][0] == l1;
        int colunaIgual = jogador.pecas[linha][1] == c1;
        if(linhaIgual && colunaIgual){
            *type = jogador.pecas[linha][2];
            *result = linha;
            return 1;
        }
    }
    return 0;
}

int verifyIfUserWannaSave(char *input){
    int result = strcmp(input, "salvar");
    if(result == 0){
        return 1;
    }else{
        return 0;
    }
}

void salvarJogo(Jogador player1, Jogador player2, char *nome_arquivo, int turno)
{
    FILE *f;
    f = fopen(nome_arquivo, "w");
    fprintf(f,"%s\n",player1.nome);
    fprintf(f,"%s\n",player2.nome);
    char matriz[8][8];
    int y1, x1, y2, x2;
    for (int i = 0; i < 8; i++) for (int j = 0; j <8; j++) matriz[i][j] = '-';
    for(int linha = 0; linha < player1.qtd_pecas; linha ++){
        y1 = player1.pecas[linha][0]; 
        x1 = player1.pecas[linha][1];
        matriz[y1][x1] = player1.pecas[linha][2];
    }
    for(int linha = 0; linha < player2.qtd_pecas; linha ++){
        y2 = player2.pecas[linha][0];
        x2 = player2.pecas[linha][1];
        matriz[y2][x2] = player2.pecas[linha][2];
    }

    for(int linha = 7; linha >= 0; linha--)
    {
        for(int coluna = 0; coluna < 8; coluna++)
        {
            fprintf(f,"%c ",matriz[linha][coluna]);
        }
        fprintf(f,"\n");
    }
    fprintf(f,"\n%d", turno);
    fclose(f);
}


void getInputDuringGame(const char *message, char* input, int turno, Jogador jogador, Jogador adversario){
    getInputFromUser(message, input);
    int result = strcmp(input, "salvar");
    while(result == 0){
        char nome[50];
        getInputFromUser("Digite o nome do arquivo para salvar: ", nome);
        salvarJogo(jogador, adversario,nome,turno);
        printf("arquivo salvo com sucesso em %s\n", nome);
        getInputFromUser(message, input);
        result = strcmp(input, "salvar");
    }
}