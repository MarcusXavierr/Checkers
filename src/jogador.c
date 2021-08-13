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