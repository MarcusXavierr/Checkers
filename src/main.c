//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "colors.h"
#include "jogador.h"

void getMenuInput(int *choice, const char *message);
void getInputFromUser(const char *message, char* input);
void validateIfUserWantQuit(char *input);

int main(int argc, char *argv[])
{   
    //Informações úteis para todo o programa;
    Jogador jogador1, jogador2;
    //
    // TODO: Depois de finalizar o menu, mover todo esse código para um arquivo chamado menu.c
    int escolha, qtd_jogadores;
    
    printf("Bem vindo ao jogo de Damas\nO que deseja fazer:\n\n");
    printf("1. Começar novo jogo\n2. Continuar um novo jogo\n\n");
    getMenuInput(&escolha, "Escolha a opção (digite ”sair” em qualquer lugar para sair do jogo): ");
    if(escolha == 1)
    {
        getMenuInput(&qtd_jogadores, "Digite a quantidade de jogadores <1 / 2 >: ");
        if(qtd_jogadores == 1){
            getInputFromUser("Digite o nome do Jogador 1 (pedra branca - “o”): ", jogador1.nome);     
        }
        else{
            getInputFromUser("Digite o nome do Jogador 1 (pedra branca - “o”): ", jogador1.nome);
            getInputFromUser("Digite o nome do Jogador 2 (pedra escura - “x”): ", jogador2.nome);
        }
    }
    if(escolha == 2)
    {
        char nome_arquivo[MAX_INPUT];
        getInputFromUser("Digite o nome do arquivo: ", nome_arquivo);
        // TODO: Implementar lógica para pegar os dados do jogo salvo. Mas antes você precisa ter um jogo para salvar
    }
    
    printf("%s\n%s\n",jogador1.nome, jogador2.nome); //* Só pra testar mesmo
    return 0;
}

void getMenuInput(int *choice, const char *message)
{   
    char *input = malloc(sizeof(char) * MAX_INPUT);
    getInputFromUser(message, input);
    // validateIfUserWantQuit(input);
    while(input[0] != '1' && input[0] != '2'){ //Tô recebendo char e não inteiro
        printf(BOLD("\nVocê digitou uma informação errada, por favor digite novamente\n"));
        getInputFromUser(message, input);
    }
    if(input[0] == '1') *choice = 1;
    else *choice = 2;
        
}


void getInputFromUser(const char *message, char* input)
{
    printf("%s", message);
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = '\0';
    validateIfUserWantQuit(input);
}

void validateIfUserWantQuit(char *input)
{
    int result = strcmp(input, "sair");
    if(result == 0)
    {
        printf("Tchau!\n");
        exit(0);
    }
}