//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogador.h"
#include "utils/colors.h"
#include "utils/constants.h"
void printMenu(Jogador *jogador1, Jogador *jogador2, int *rodada, char *nome_arquivo) {
    int escolha, qtd_jogadores;
    printf("Bem vindo ao jogo de Damas\nO que deseja fazer:\n\n");
    printf("1. Começar novo jogo\n2. Continuar um novo jogo\n\n");
    getMenuInput(&escolha, "Escolha a opção (digite ”sair” em qualquer lugar para sair do jogo): ");
    if (escolha == 1) {
        *rodada = 1;
        jogador1->qtd_pecas = 12;
        jogador2->qtd_pecas = 12;
        preencherMatriz(&jogador1->pecas, 'o');
        preencherMatriz(&jogador2->pecas, 'x');
        getMenuInput(&qtd_jogadores, "Digite a quantidade de jogadores <1 / 2 >: ");
        if (qtd_jogadores == 1) {
            getInputFromUser("Digite o nome do Jogador 1 (pedra branca - “o”): ", jogador1->nome);
            strcpy(jogador2->nome, "bot2\0");

        } else {
            getInputFromUser("Digite o nome do Jogador 1 (pedra branca - “o”): ", jogador1->nome);
            getInputFromUser("Digite o nome do Jogador 2 (pedra escura - “x”): ", jogador2->nome);
        }
    }
    if (escolha == 2) {
        if (nome_arquivo[0] == '\0') {
            getInputFromUser("Digite o nome do arquivo: ", nome_arquivo);
        }
        carregarJogo(jogador1, jogador2, nome_arquivo, rodada);
    }
}

void getMenuInput(int *choice, const char *message) {
    char *input = malloc(sizeof(char) * MAX_INPUT);
    getInputFromUser(message, input);
    while (input[0] != '1' && input[0] != '2') {  //Tô recebendo char e não inteiro
        printf(BOLD("\nVocê digitou uma informação errada, por favor digite novamente\n"));
        getInputFromUser(message, input);
    }
    if (input[0] == '1')
        *choice = 1;
    else
        *choice = 2;
}

void carregarJogo(Jogador *jogador1, Jogador *jogador2, char *nome_arquivo, int *rodada) {
    //Jogador1 tem peças do tipo 'o' ou 'O', e jogador2 tem peças 'x' ou 'X'
    FILE *f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        printf(BOLD(RED("Erro ao ler o arquivo!\nDigite o nome de um arquivo que existe\n")));
        exit(1);
    }
    jogador1->pecas = criaMatriz(12, 3);  //Primeiro eu crio um matriz q tem 12 peças e dps vou diminuindo caso leia menos peças
    jogador2->pecas = criaMatriz(12, 3);
    int index_jogador1 = 0;
    int index_jogador2 = 0;
    int bufferLength = 50;
    char buffer[bufferLength];
    readNameFromFile(jogador1, f, buffer, bufferLength);
    readNameFromFile(jogador2, f, buffer, bufferLength);
    for (int linha = 7; linha >= 0; linha--) {
        char pecas[20];
        fgets(buffer, bufferLength, f);
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(pecas, remove_white_spaces(buffer));
        for (int coluna = 0; coluna < 8; coluna++) {
            if (pecas[coluna] == 'o' || pecas[coluna] == 'O') {
                jogador1->pecas[index_jogador1][0] = linha;
                jogador1->pecas[index_jogador1][1] = coluna;
                jogador1->pecas[index_jogador1][2] = pecas[coluna];
                index_jogador1++;
            } else if (pecas[coluna] == 'x' || pecas[coluna] == 'X') {
                jogador2->pecas[index_jogador2][0] = linha;
                jogador2->pecas[index_jogador2][1] = coluna;
                jogador2->pecas[index_jogador2][2] = pecas[coluna];
                index_jogador2++;
            }
        }
    }
    jogador1->qtd_pecas = index_jogador1;
    jogador2->qtd_pecas = index_jogador2;
    fgets(buffer, bufferLength, f);
    buffer[strcspn(buffer, "\n")] = '\0';
    *rodada = atoi(buffer);
}

void readNameFromFile(Jogador *jogador, FILE *f, char *buffer, int bufferLength) {
    fgets(buffer, bufferLength, f);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(jogador->nome, buffer);
}

char *remove_white_spaces(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}