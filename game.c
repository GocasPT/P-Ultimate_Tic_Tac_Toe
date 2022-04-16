// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
//Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include "game.h"

int checkWin(char **p, int nLin, int nCol){
    int i, j;

    for(i=0; i<nLin; i++){
        if(p[i][0] != '_'){
            for(j=0; j<nCol-1 && p[i][j] == p[i][j+1]; j++);
            if(j==nCol-1)
                return 1;
        }
    }
    return 0;
}