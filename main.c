// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include "matdin.h"
#include "game.h"
#include "utils.h"

#define N 3 // Númeor de linhas e colunas das Matrizes
#define mTLength 9 // Númeor de miniTabuleiros criados

typedef struct miniTabuleiro miniTab; // miniTabuleiro = miniTab

struct  miniTabuleiro
{
    char **grid; // Matriz do miniTabuleiro
    int numName; // Numero do miniTabuleiro (1 a 9)
    char value; // Valor do miniTabuleiro no Tabuleiro (Empate, X ou O)
};


int main(){
    int i, j; // Variaveis aleatórias
    int coor, x, y; // Variaveis de coordenadas
    int jogadas, jogador, peca, fimDeJogo; // Variaveis do jogo
    char **guideTab; // Matriz guia

    char point;

    initRandom();

    fimDeJogo = 0;

    // Escolhe qual jogador que começa
    jogador = intUniformRnd(0, 1);

    miniTab mT[mTLength]; // Minitabuleiros

    //for (i = 0; (i < 9) && (mT[i].grid != NULL) ; i++){ → parte do "caso falha a criação da matriz"
    for (i = 0; i < 9 ; i++){
        mT[i].grid = criaMat(N, N);

        if(mT[i].grid==NULL){ // Caso falha na criação na matriz
            printf("%d - Error!!", i+1);
        }
    }

    printf("\n");

    guideTab = criaMat(N, N);
    guideTab = prencMat(guideTab, N, N);

    //mostraMat(mT[0].grid,3,3);
    mostraMat(guideTab, N, N);
    //mostraMat(TabuleiroGlobal,3,3);
    jogadas = 0;

    //while (fimDeJogo != 1 && jogadas < (N * N * mTLength))
    while(fimDeJogo != 1 && jogadas < mTLength)
    {
        if(jogador == 0){
            peca = 'O';
            jogador = 1;
        }else{
            peca = 'X';
            jogador = 0;
        }

        //Bloco de leitura e de verificação
        do
        {
            coor = 0;

            printf("Jogador %c: ", peca);
            scanf("%d", &coor);
            printf("\n");

            //!!Uso de Switch aqui!!
            // Bloco de commandos de jogo
            if(coor == 69){//← set command number (mTLength + i)
                mostraGuia(guideTab, N, N);
            }
            
            // Bloco de funciunaliade de peça
            else{
                // Trasforma o numero de 1 a 9 em coordenadas do tabuleiro
                x = 0;
                while(coor > N){
                    coor -= N;
                    x++;
                }
                y = coor - 1;

                // Validade de jogada e posicionamento de peça
                point = getPos(mT[0].grid, x, y);
                if(point != '_'){
                    printf("Jogada invalida!!\n");
                    mostraMat(mT[0].grid, N, N);
                    coor = mTLength + 1;
                }else{
                    setPos(mT[0].grid, x, y, peca);
                }
            }
        } while(coor > mTLength);     

        mostraMat(mT[0].grid, N, N);

        // Validade de vitoria
        if(checkWin(mT[0].grid, N, N)){
            fimDeJogo = 1;
        }
        jogadas++;
    }
    
    printf("Acabou");

    return 0;
}
