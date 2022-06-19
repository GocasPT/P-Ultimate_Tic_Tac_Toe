// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "matdin.h"
#include "files.h"

void saveFile(int jogadas, int state, int player, char** globalTab, int globalTabSize, miniTab* mT, int mTLenght, phisto lista){    
    FILE *f;
    int i,j;

    f = fopen("jogo.bin", "wb");

    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
        
    fwrite(&jogadas, sizeof(int), 1, f);
    fwrite(&state, sizeof(int), 1, f);
    fwrite(&player, sizeof(int), 1, f);

    for(i=0; i < globalTabSize; i++){
        fwrite(globalTab[i], sizeof(globalTab[i][0]), globalTabSize, f);
    }

    for(i=0; i < mTLenght; i++){
        for(j=0; j < 3; j++){
            fwrite(mT[i].grid[j], sizeof(mT[i].grid[j][0]), 3, f);
        }
        fwrite(&mT[i].numName, sizeof(int), 1, f);
        fwrite(&mT[i].value, sizeof(char), 1, f);
    }

    while(lista != NULL){
        fwrite(&(lista->numItem), sizeof(int), 1, f);
        fwrite(&(lista->player), sizeof(char), 1, f);

        for(i=0; i < 3; i++){
            fwrite(lista->bigScreen[i], sizeof(lista->bigScreen[i][0]), 3, f);
        }

        fwrite(&(lista->numTab), sizeof(int), 1, f);

        for(i=0; i < 3; i++){
            fwrite(lista->screen[i], sizeof(lista->screen[i][0]), 3, f);
        }

        lista = lista->prox;
    }
    
    fclose(f);  
}

phisto loadFile(int* jogadas, int* state, int* player, char** globalTab, int globalTabSize, miniTab* mT, int mTLenght){
    phisto aux=NULL;
    FILE *f;
    int i,j,k;

    int* numItem = malloc(sizeof(int));
    char* playerChar = malloc(sizeof(char));
    char** bigScreen = criaMat(3,3);
    int* numTab = malloc(sizeof(int));
    char** screen = criaMat(3,3);

    f = fopen("jogo.bin", "rb");

    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        //return NULL;
    }

    fread(jogadas, sizeof(int), 1, f);
    fread(state, sizeof(int), 1, f);
    fread(player, sizeof(int), 1, f);

    //  defeito de entrada de loop O → X e X → O
    if(*player == 0)
        (*player)++;
    else
        (*player)--;
    
    for(i=0; i < globalTabSize; i++){
        fread(globalTab[i], sizeof(globalTab[i][0]), globalTabSize, f);
    }

    for(i=0; i < mTLenght; i++){
        for(j=0; j < 3; j++){
            fread(mT[i].grid[j], sizeof(mT[i].grid[j][0]), 3, f);
        }

        fread(&mT[i].numName, sizeof(int), 1, f);

        fread(&mT[i].value, sizeof(char), 1, f);
    }

    k=*jogadas;

    while(k != 0){
        fread(numItem, sizeof(int), 1, f);
        fread(player, sizeof(char), 1, f);

        for(i=0; i < 3; i++){
            fread(bigScreen[i], sizeof(bigScreen[i][0]), 3, f);
        }

        fread(numTab, sizeof(int), 1, f);

        for(i=0; i < 3; i++){
            fread(screen[i], sizeof(screen[i][0]), 3, f);
        }

        aux = addPlay(aux, *numItem, *playerChar, bigScreen, *numTab, screen);
        k--;
    }
    fclose(f);
    return aux;
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