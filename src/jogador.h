#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[50];
    int **pecas; //* Aqui eu faço uma matriz com todas as posições de todas as peças do jogador
    char tipo_peca; //* C = clara, E = escura
} Jogador;



#endif