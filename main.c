// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include "matdin.h"
#include "game.h"

typedef struct miniTabuleiro miniTab;

struct  miniTabuleiro
{
   char **grid;
   int numName;
   char value;
};


int main(){
    int i;

    char point, peca;
    int jogador, jogadas, endGame, x, y;

    endGame = 0;
    jogador = 0;

    miniTab mT[9];

    //for (i = 0; (i < 9) && (mT[i].grid != NULL) ; i++) → parte do "caso falha a criação da matriz"
    for (i = 0; i < 9 ; i++)
    {
        mT[i].grid = criaMat(3, 3);

        if(mT[i].grid==NULL){ //Caso falha na criação na matriz
            printf("%d - Error!!", i+1);
        }
            
        printf("%d - Certo\n", i+1);
    }
    
    mostraMat(mT[0].grid,3,3);
    jogadas = 0;

    while (endGame != 1 && jogadas < 9)
    {
        printf("faz a sua jogada: ");
        scanf("%d %d", &x, &y);

        point = getPos(mT[0].grid,x,y);
        if(point != '_'){
            printf("Jogada invalida!!\n");
        }else{
            if(jogador == 0){
                peca = '0';
                jogador++;
            }else{
                peca = 'X';
                jogador--;
            }

            setPos(mT[0].grid, x, y, peca);
        }

        mostraMat(mT[0].grid,3,3);

        if(checkWin(mT[0].grid,3,3))
        {
            endGame = 1;
        }
        jogadas++;
    }
    
    printf("Acabou");

    return 0;
}
