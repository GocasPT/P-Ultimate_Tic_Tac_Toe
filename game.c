// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include "game.h"

int checkWin(char **p, int nLin, int nCol){
    int i, j;


    //Verifia as linhas
    for(i=0; i<nLin; i++){
        if(p[i][0] != '_'){
            for(j=0; j<nCol-1 && p[i][j] == p[i][j+1]; j++);
            if(j==nCol-1)
                return 1;
        }
    }

    //Verifia as colunas
    for(i=0; i<nCol; i++){
        if(p[0][i] != '_'){
            for(j=0; j<nLin-1 && p[j][i] == p[j+1][i]; j++);
            if(j==nLin-1)
                return 1;
        }
    }

    //Verifia as diagonais
    if(p[0][0] != '_'){
        for(i=0; i<nLin-1 && p[i][i] == p[i+1][i+1]; i++); //Esquerda para a direita de cima para baxio
        if(i==nLin-1)
            return 1;
    }
    
    if(p[nLin-1][0] != '_'){
        for(i=0; i<nCol-1 && p[nLin-1-i][i] == p[nLin-2-i][i+1]; i++); //Esquerda para a direita de baico para cima
        if(i==nCol-1)
            return 1;
    }

    return 0;
}

void mostraGuia(char **p, int nLin, int nCol){
    int i,j;

    printf("\n");
    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++)
            printf("%c\t", p[i][j]);
        putchar('\n');
    }
    printf("\n");
}