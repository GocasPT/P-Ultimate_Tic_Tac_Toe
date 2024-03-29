// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}