// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include <stdlib.h>
#include "matdin.h"

void libertaMat(char** p, int nLin){
    int i;

    for(i=0; i<nLin; i++)
        free(p[i]);
    free(p);
}

char** criaMat(int nLin, int nCol){
    char **p = NULL;
    int i, j;

    p = malloc(sizeof(char*) * nLin);
    if(p == NULL)
        return NULL;

    for(i=0; i<nLin; i++){
        p[i] = malloc(sizeof(char) * nCol);
        if(p[i] == NULL){
            libertaMat(p, i-1);
            return NULL;
        }
        for(j=0; j<nCol; j++)
            p[i][j] = '_';
    }
    return p;
}

void setPos(char **p, int x, int y, char c){
    p[x][y] = c;
}

char getPos(char **p, int x, int y){
    return p[x][y];
}

void mostraMat(char **p, int nLin, int nCol){
    int i,j;

    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++)
            printf("%c\t", p[i][j]);
        putchar('\n');
    }
    printf("\n");
}

char** prencMat(char **p, int nLin, int nCol){
    int i, j, k = 1;
    char num;

    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++){
            num = k + '0';
            setPos(p, i, j, num);
            k++;
        }
    }

    return p;
}

char** copyMat(char **p, int nLin, int nCol){
    int i, j;
    char **out = criaMat(nLin, nCol);
    
    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++){
            out[i][j] = p[i][j];
        }
    }
    
    return out;
}