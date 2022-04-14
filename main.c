// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include "matdin.h"

struct miniTab
{
   char **grid;
   int numName;
   char value;
} miniTab1;


int main(){
    char **tab;

    tab = miniTab1.grid;

    tab = criaMat(3, 3);

    if(tab!=NULL){ //Caso a criação seja um sucesso, escreve a matriz na consola
        mostraMat(tab, 3, 3);
    }

    return 0;
}
