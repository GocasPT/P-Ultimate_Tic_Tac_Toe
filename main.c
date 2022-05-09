// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "matdin.h"
#include "game.h"
#include "utils.h"

#define N 3   // Númeor de linhas e colunas das Matrizes miniTabuleiro/miniTab
#define S 3   // Númeor de linhas e colunas da Matrizes globalTab
#define mTLength 9   // Númeor de miniTabuleiros criados

typedef struct miniTabuleiro miniTab;   // miniTabuleiro <=> miniTab

struct  miniTabuleiro
{
    char **grid;    // Matriz do Mini Tabuleiro
    int numName;    // Numero do Mini Tabuleiros (1 a 9)
    char value;   // Valor do Mini Tabuleiros para o Tabuleiro global (X ou O)
};


int main(){
    int i, j;   // Variaveis para ciclos
    int coor = 10, x, y;   // Variaveis de coordenadas
    int jogadas = 0, jogador, fimDeJogo = 0, target, local;   // Variaveis do jogo (int)
    char cmd;   // Variavel de commando
    char point, peca, winner;   // Variaveis de jogo (char)
    char tab[] = "Global";  // Variavel de string 
    char **guideTab, **globalTab;   // Matriz do Tabuleiro guia, Matriz do Tabuleiro global

    initRandom();

    // Escolhe qual jogador que começa
    jogador = intUniformRnd(0, 1);

    // Criar tabela global
    globalTab = criaMat(S, S);

    // Criar os Mini Tabuleiros
    miniTab mT[mTLength];

    for (i = 0; i < 9 ; i++){
        mT[i].grid = criaMat(N, N);

        if(mT[i].grid==NULL){   // Caso falha na criação na matriz
            printf("%d - Error!!\n", i+1);
        }

        mT[i].numName = i + 1;
        mT[i].value = 95;   // <=> mT[i].value = "_";
    }

    // Criar a tabela guia
    guideTab = criaMat(N, N);
    guideTab = prencMat(guideTab, N, N);

    // Mostra tabuleiro global (Inicio de jogo)
    printf("Tabela: %s\n", tab);
    mostraMat(globalTab, S, S);

    // Inicia loop do jogo
    while (fimDeJogo != 1 && jogadas < (N * N * mTLength))
    {
        // Bloco de seleção de personagem de jogada
        if(jogador == 0){
            peca = 79;   // <=> peca = "O";
            jogador = 1;
        }else{
            peca = 88;   // <=> peca = "X";
            jogador = 0;
        }

        //Bloco de leitura e de verificação
        do
        {
            printf("Jogador %c: ", peca);
            scanf("%c", &cmd);
            cmd = tolower(cmd); // Transforma o cmd em lower case (ex: L → l)
            printf("\n");

            // Bloco de commandos de jogo
            switch (cmd)
            {
                // Comando guide - mostrar o Tabuleiro guia
                case 'g': 
                    printf("Tabuleiro Guia: \n");
                    mostraMat(guideTab, N, N);
                    coor = 10;
                    break;

                // Comando tab - mostra o Tabuleiro global
                case 't':
                    printf("Tabuleiro Global: \n");
                    mostraMat(globalTab, S, S);
                    coor = 10;
                    break;

                // Comando local - mostra o Tabuleiro local
                case 'l':
                    if(!jogadas){
                        printf("Comando disponivel depois de colocar a primeira peca\n");
                    }else{
                        printf("Tabela: %d\n", local + 1);
                        mostraMat(mT[target].grid, N, N);
                    }
                    coor = 10;
                    break;

                // Comando alll - mostra todos os tabuleiros (Tabuleiro global + Mini Tabuleiro)
                case 'a':
                    printf("Tabela: %s\n", tab);
                    mostraMat(globalTab, S, S);
                    for(i=0; i<mTLength; i++){
                        printf("Tabela: %d\n", i+1);
                        mostraMat(mT[i].grid, N, N);
                    }
                    coor = 10;
                    break;

                // Comando de ajuda - lista de comandos que os jogadores podem fazer
                case 'h':
                    printf("Tabela de comandos:\n 1 a 9 - Local de jogada de peca\n g - Mostra guia de jogada\n t - Mostra Tabuleiro Global\n l - Mostra Mini Tabuleiro\n a - Mostra todas os Tabuleiros (Tabuleiro Global + Minis Tabuleiros)\n");
                    coor = 10;
                    break;

                // Comando exit - 
                case 'e':
                    break;

                // Bloco de funciunaliade de peça
                default: 
                    coor = cmd - '0';

                    if(!coor){
                        printf("Comando não existe");
                        break;
                    }

                    target = coor - 1;

                    // Na primeira jogada, o jogador decide em que miniTabuleiro começar
                    if (jogadas == 0)
                    {
                        printf("Tabela: %d\n", target + 1);
                        mostraMat(mT[target].grid, N, N);

                        local = target;

                        printf("Jogador %c: ", peca);
                        scanf("%d", &coor);
                        printf("\n");

                        target = coor - 1;
                    }

                    coorTrans(coor, N, &x, &y);

                    // Validade de jogada e posicionamento de peça
                    point = getPos(mT[local].grid, x, y);
                    if(point != '_'){
                        printf("Jogada invalida!!\n");
                        mostraMat(mT[local].grid, N, N);
                        coor = mTLength + 1;
                    }else{
                        coorTrans(coor, N, &x, &y);
                        setPos(mT[local].grid, x, y, peca);
                    }

                    jogadas++;
                    break;
            }

            fflush(stdin);   // Limpa o input de commando

        } while(coor > mTLength);     

        // Blocode de validação de vitoria
        if(mT[local].value == 95){   // <=> if(mT[local].value == "_");
            if(checkWin(mT[local].grid, N, N)){
                mT[local].value = peca;
                coorTrans(local + 1, N, &x, &y);
                setPos(globalTab, x, y, peca);
                printf("Jogador %c ganhou o Mini Tabbuleiro %d", peca, mT[local].numName);
            }

            if(checkWin(globalTab, S, S)){
                fimDeJogo = 1;
                winner = 1;
            }else{
                printf("Tabela: %d\n", target + 1);
                mostraMat(mT[target].grid, N, N);
            }
        }

            local = target;
    }
    
    if(!winner){
        printf("Jogo acabou empatado");
    } else {
        printf("Parabens, o jogador %c ganhou o jogo.", peca);
        mostraMat(globalTab, S, S);
    }

    return 0;
}