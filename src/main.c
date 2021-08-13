//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32


#include "main.h"

void getMenuInput(int *choice, const char *message);

int main(int argc, char *argv[])
{   

    // TODO: Depois de finalizar o menu, mover todo esse código para um arquivo chamado menu.c
    int max_nome = 50;
    int escolha, qtd_jogadores;
    char nome_jogador_1[50], nome_jogador_2[50];
    printf("Bem vindo ao jogo de Damas\nO que deseja fazer:\n\n");
    printf("1. Começar novo jogo\n2. Continuar um novo jogo\n");
    getMenuInput(&escolha, "Escolha a opção (digite ”sair” em qualquer lugar para sair do jogo): ");
    if(escolha == 2) ;//TODO: Pegar o input do usuario pra abrir o txt e continuar o jogo
    getMenuInput(&qtd_jogadores, "Digite a quantidade de jogadores <1 / 2 >: ");
    if(qtd_jogadores == 2)
    {
        getchar();
        printf("Digite o nome do Jogador 1 (pedra branca - “o”): ");
        scanf("%[^\n]%*c",nome_jogador_1);
        printf("Digite o nome do Jogador 2 (pedra escura - “x”): ");
        scanf("%[^\n]%*c",nome_jogador_2);
    }
    printf("%s\n%s\n",nome_jogador_1, nome_jogador_2);
    return 0;
}

void getMenuInput(int *choice, const char *message)
{   
    int _choice = 0;
    printf(message);
    errorMenuInput:
    scanf("%d", &_choice);
    if(_choice != 1 && _choice != 2 && !isdigit(_choice))
    {   
        printf("Erro ao processar seu input, por favor, digite novamente\n");
        printf(message);
        getchar();
        goto errorMenuInput;
    }
    *choice = _choice;
    
        
}