// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>

#include "game.h"
#include "files.h"

void saveFile(plista p, int num, miniTab *mTab, int nLinMintab, char **Tab, int nLinTab){
    FILE *f;
    int i;

    f = fopen("jogo.bin", "wb");

    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    fwrite(&num, sizeof(int), 1, f);
    fwrite(p, sizeof(plista), num, f);

    fwrite(Tab, sizeof(char**), nLinTab, f);
    fwrite(mTab, nLinTab, nLinMintab, f);

    fclose(f);
}

void loadFile(plista *p, int *total){
    FILE *f;
    plista aux;

    *total = 0;
    if( (f = fopen("jogo.bin", "rb")) == NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    fread(p, sizeof(plista), 1, f);

    while (feof(f) == 0)
    {
        p[(*total)++] = aux;
        read(&aux, sizeof(plista), 1, f);
    }

    fclose(f);
}

int saveExit(){
    FILE *f;

    f = fopen("jogo.bin", "rb");
    if(f==NULL)
        return 0;
    else
        return 1;
}

void saveCreditFile(){
    
}