//20.2.4002
//Marcus Vinicius Pereira Xavier
//Turma 32

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "utils/colors.h"
#include "jogador.h"
#include "menu.h"


int main(int argc, char *argv[])
{   
    //Informações úteis para todo o programa;
    Jogador jogador1, jogador2;
    //
    // TODO: Depois de finalizar o menu, mover todo esse código para um arquivo chamado menu.c
    
    printMenu(&jogador1, &jogador2);
    printf("%s\n%s\n",jogador1.nome, jogador2.nome); //* Só pra testar mesmo
    return 0;
}




