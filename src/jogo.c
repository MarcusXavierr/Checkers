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

void jogada(Jogador *jogador, Jogador *adversario, int *turno, char *nome_arquivo)
{
    char message[100], input[50], peca;
    if(*turno==1) peca = 'o';
    else if(*turno==2) peca = 'x';
    int c1, c2, l1, l2, linha;
    int pecas_comidas = 0;
    char *tipo = malloc(sizeof(char));
    *tipo = '\0';
    sprintf(message, "%s (%c), é a sua vez: ", jogador->nome, peca);
    int is_bot = strcmp(jogador->nome, "myself");
    if(is_bot == 0){
        jogarComBot( &c1, &c2, &l1, &l2, &linha, tipo, jogador, adversario, *turno, &pecas_comidas);
        sleep(1);
    }else{
        lerJogada(message, input, &c1, &c2, &l1, &l2, &linha, tipo, jogador, adversario, *turno, &pecas_comidas, nome_arquivo);
    }
    
    if(*tipo == 'x'){
        if(l2 == 7) {
            virarDama(jogador,l1, c1);
            printf("Parabéns %s, você conseguiu uma dama!\n", jogador->nome);
        }
    }else if(*tipo == 'o'){
        if(l2 == 0) {
            virarDama(jogador, l1, c1);
            printf("Parabéns %s, você conseguiu uma dama!\n", jogador->nome);
        }
    }

    jogador->pecas[linha][0] = l2;
    jogador->pecas[linha][1] = c2;
    free(tipo);
    int podeComer = verificarSePedraPodeComer(*jogador, *adversario, l2, c2);
    if(podeComer == 0 || pecas_comidas == 0){
        if(*turno == 1){
            *turno = 2;
            return;
        }
        else if(*turno == 2) *turno = 1;
    }
    
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

void lerJogada(char *message, char *input, int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador, Jogador *adversario, int turno, int *pecas_comidas, char *nome_arquivo)
{   
    int is_valid, qtd_input;
    int result;
    do{
        getInputDuringGame(message, input, turno, *jogador, *adversario, nome_arquivo);
        result = validateInput(input, c1, c2,l1,l2, jogador, adversario, linha, tipo, turno, nome_arquivo);
        if(result == 0) {
            printf(BOLD("\nInput inválido, tente novamente\n"));
            continue;
        }
        if(result == -1) {
            printf(BOLD(RED("Você soprou! Tente novamente\n")));
            continue;
        }
        int isDama = verifyIfIsDama(*tipo);
        if(isDama == -1) is_valid = 0;
        if(isDama == 0){
            if(calcularDistanciaMovimento(*l1, *c1, *l2, *c2) == 2){
                is_valid = comerComPecaComum(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
            }
        }
        else if(isDama == 1){
            is_valid = comerComDama(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
        }

        if(result == 0 || is_valid == 0) printf(BOLD("\nInput inválido, tente novamente\n"));
    }while(result == 0 || is_valid == 0 || result == -1);
    
    
}

int verifyIfIsDama(char tipo)
{
    if(tipo == 'x' || tipo == 'o')
        return 0;

    if(tipo == 'X' || tipo ==  'O')
        return 1;
    
    return -1;
}

int comerComDama(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2, int *pecas_comidas)
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
        *pecas_comidas = *pecas_comidas + 1;
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

int comerComPecaComum(Jogador *jogador, Jogador *adversario, int l1, int c1, int l2, int c2, int *pecas_comidas){
    int xM, yM, localizacao_peca;
    char tipo;
    xM = (c1 + c2) / 2;
    yM = (l1 + l2) / 2;
    int exists = verifyIfPieceExists(*adversario,yM, xM, &localizacao_peca, &tipo);
    if(exists){
        removerPeca(adversario, localizacao_peca);
        *pecas_comidas = *pecas_comidas + 1;
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
    if(turno == 1){
        fprintf(f,"%s\n",player1.nome);
        fprintf(f,"%s\n",player2.nome);
    }else if(turno == 2){
        fprintf(f,"%s\n",player2.nome);
        fprintf(f,"%s\n",player1.nome);
    }
    
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
    fprintf(f,"%d", turno);
    fclose(f);
}


void getInputDuringGame(const char *message, char* input, int turno, Jogador jogador, Jogador adversario, char *nome_arquivo){
    getInputFromUser(message, input);
    int result = strcmp(input, "salvar");
    while(result == 0){
        if(nome_arquivo[0] == '\0'){
            getInputFromUser("Digite o nome do arquivo para salvar: ", nome_arquivo);
        }
        
        salvarJogo(jogador, adversario,nome_arquivo,turno);
        printf(BOLD("arquivo salvo com sucesso em %s\n"), nome_arquivo);
        getInputFromUser(message, input);
        result = strcmp(input, "salvar");
    }
}

void virarDama(Jogador *jogador, int l1, int c1){
    int linha;
    char tipo;
    verifyIfPieceExists(*jogador, l1,c1, &linha, &tipo);
    jogador->pecas[linha][2] = tipo - 32;
}


float calcularCoeficienteAngular(int y1, int x1, int y2, int x2){
    float coeficiente = (float)(y1 - y2) / ((float)x1 - x2);
    coeficiente = fabs(coeficiente);
    return coeficiente;
}

void jogarComBot(int *c1, int *c2, int *l1, int *l2, int *linha, char *tipo, Jogador *jogador, Jogador *adversario, int turno, int *pecas_comidas){
    char input[20];
    char nome_arquivo[20];
    int result, is_valid;
    int tentativas = 0;
    struct timeval tm;
    do{
        tentativas++;
        gettimeofday(&tm, NULL);
        srand(tm.tv_usec + tentativas);
        int line = rand() % ((jogador->qtd_pecas - 1) + 1 - 0) + 0;
        char cL1 = convertNumToChar(jogador->pecas[line][0]);
        int nC1 = jogador->pecas[line][1] + 1;
        int tmp = ( rand() % (7 + 1 - 0) + 0 );
        char cL2 = convertNumToChar(tmp);
        int nC2 = (rand() % (7 + 1 - 0) + 0) + 1;
        sprintf(input, "%c%d %c%d", cL1, nC1, cL2, nC2);
        result = validateInput(input, c1, c2,l1,l2, jogador, adversario, linha, tipo, turno, nome_arquivo );
        if(result != 1) continue;
        int isDama = verifyIfIsDama(*tipo);
        if(isDama == -1) is_valid = 0;
        if(isDama == 0){
            if(calcularDistanciaMovimento(*l1, *c1, *l2, *c2) == 2){
                is_valid = comerComPecaComum(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
            }
        }
        else if(isDama == 1){
            is_valid = comerComDama(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
        }
        if(is_valid == 1) return;
        
    }while(tentativas < 20000);


    for(int line = 0; line < jogador->qtd_pecas; line++){
        char cL1 = convertNumToChar(jogador->pecas[line][0]);
        int nC1 = jogador->pecas[line][1] + 1;
        for(int y = 0; y < 8; y++){
            for(int x = 0; x < 8; x++){
                char cL2 = convertNumToChar(y);
                int nC2 = x + 1;
                sprintf(input, "%c%d %c%d", cL1, nC1, cL2, nC2);
                
                result = validateInput(input, c1, c2,l1,l2, jogador, adversario, linha, tipo, turno, nome_arquivo );
                if(result != 1) continue;
                // printf("%s\n", input);
                int isDama = verifyIfIsDama(*tipo);
                if(isDama == -1) is_valid = 0;
                if(isDama == 0){
                    if(calcularDistanciaMovimento(*l1, *c1, *l2, *c2) == 2){
                        is_valid = comerComPecaComum(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
                    }else if(calcularDistanciaMovimento(*l1, *c1, *l2, *c2) == 1){
                        is_valid = 1;
                    }
                }
                else if(isDama == 1){
                    is_valid = comerComDama(jogador, adversario, *l1, *c1, *l2, *c2, pecas_comidas);
                }
                if(is_valid == 1) return;
            }
        }
    }
    
    
}