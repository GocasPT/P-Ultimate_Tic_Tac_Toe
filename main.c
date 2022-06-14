// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <ctype.h>

#include "files.h"
#include "game.h"
#include "matdin.h"
#include "utils.h"

int main(){
    int selection, mode = 0, choose = 0, save = 0;   // Modo de jogo (0 → PvP; 1 → PvM)
    char resposta;

    //  Bloco de menu
    while (!choose)
    {
        printf("\t+------------------------------------+\n"
            "\t|                                     |\n"
            "\t|  Bem-vindo ao Ultimate Tic Tac Toe  |\n"
            "\t|                                     |\n"
            "\t+-------------------------------------+\n");

        printf("\t\t+----------------+\n"
            "\t\t|                |\n"
            "\t\t|  New game - 1  |\n"
            "\t\t|                |\n"
            "\t\t+----------------+\n");

        if(saveFileExists()){
            printf("\t\t+----------------+\n"
                "\t\t|                |\n"
                "\t\t|  Load save - 2 |\n"
                "\t\t|                |\n"
                "\t\t+----------------+\n");
        }

        printf("\t\t+----------------+\n"
            "\t\t|                |\n"
            "\t\t|    Exit - 3    |\n"
            "\t\t|                |\n"
            "\t\t+----------------+\n");

        scanf("%d", &selection);
        fflush(stdin);
        printf("\n\n\n\n\n");

        switch (selection)
        {
        case 1:
            printf("\t+------------------------------------+\n"
                "\t|                                     |\n"
                "\t|        Qual modo vai querer?        |\n"
                "\t|                                     |\n"
                "\t+-------------------------------------+\n");

            printf("\t\t+----------------+\n"
                "\t\t|                |\n"
                "\t\t|     PvP - 1    |\n"
                "\t\t|                |\n"
                "\t\t+----------------+\n");

            printf("\t\t+----------------+\n"
                "\t\t|                |\n"
                "\t\t|     PvM - 2    |\n"
                "\t\t|                |\n"
                "\t\t+----------------+\n");

            scanf("%d", &selection);
            fflush(stdin);
            printf("\n\n\n\n\n");

            if(selection == 2)
                mode=1;
            else
                mode=0;

            //saveDelet();

            break;

        case 2:
            if(saveFileExists())
                save = 1;
                break;

        case 3:
            printf("Tem a certeza que quere sair do programa? (Y/N) ");
            scanf("%c", &resposta);
            resposta = toupper(resposta);
            if(resposta == 'Y'){
                printf("Adeus!");
                return 0;
            }
            break;
        }

        choose=1;
    }

    // Chamada da função de jogo
    printf("\t!!!!Que o jogo comece!!!!\n\n");

    startGame(mode, save);

    return 0;
}