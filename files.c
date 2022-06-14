// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>

#include "game.h"
#include "files.h"

void saveFile(phisto lista, int total){    
    FILE *f;

    f = fopen("jogo.bin", "wb");

    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
        
    fwrite(&total, sizeof(int), 1, f);

    while(lista != NULL){
        fwrite(lista, sizeof(histo), 1, f);
        lista = lista->prox;
    }
    
    fclose(f);  
}

void loadFile(phisto lista, int *total){
    FILE *f;
    
    *total = 0;

    f = fopen("jogo.bin", "rb");

    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return NULL;
    }

    fread(total, sizeof(int), 1, f);

    while(fread(lista, sizeof(histo), 1, f) != EOF){
        fread(lista, sizeof(histo), 1, f);
    }
    
    fclose(f);
    return lista;
}

int saveFileExists(){
    FILE *f;

    f = fopen("jogo.bin", "rb");
    if(f==NULL)
        return 0;
    else
        return 1;
}

void saveDelet(){
    if (remove("jogo.bin") == 0)
      printf("Deleted successfully");
   else
      printf("Unable to delete the file");
}