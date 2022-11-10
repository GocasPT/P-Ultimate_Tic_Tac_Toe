// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "matdin.h"
#include "utils.h"
#include "files.h"
#include "game.h"

#define N 3   //    Númeor de linhas e colunas das Matrizes miniTabuleiro/miniTab
#define S 3   //    Númeor de linhas e colunas da Matrizes globalTab
#define mTLength (S*S)  // Númeor de miniTabuleiros criados

phisto addPlay(phisto p, int num, char peca, char **tab, int numTab, char **miniTab){
    phisto novo, aux;

    if((novo = malloc(sizeof(histo))) == NULL)
        printf("Erro na alocacao de memoria\n");
    else{
        fillItem(novo, num, peca, tab, numTab, miniTab);
        //  Se a lista p tiver vazia, simplesmente copia o novo elemento
        if (p == NULL)
            p = novo;   
        else {
            // Percorre a lista toda até encontrar o último elemento da lista
            aux = p;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = novo;
        }
    }

    return p;
}

void fillItem(phisto p, int n, char peca, char **tab, int nT, char **mT){
    p->numItem = n;
    p->player = peca;
    p->bigScreen = copyMat(tab, S, S);
    p->numTab = nT;
    p->screen = copyMat(mT, N, N);
    p->prox = NULL;
}

void showList(phisto p, int jogadas , int modo){
    int k;

    printf("Quantas jogadas anteriores quere? (1 a 10) ");
    do{
        scanf("%d", &k);
        if(k<=0 || k>10)
            printf("Quantidade invalida!\n");
            fflush(stdin);
    }while(k<=0 || k>10);

    // jogadas-k+1 <=> num de jogadas totais - num de jogadas queres ver
    if(!((jogadas-k+1) < 0)){
        while(p->numItem != (jogadas-k)+1)
            p = p->prox;
    }
        
    printf("\n---------Historioco de jogadas---------\n");

    if(p != NULL){
        while(p != NULL){
            if(modo && p->player == 88)
                printf("Jogada: %d\tJogado por: %c (Robo)\nTabela global:\n", p->numItem, p->player);
            else
                printf("Jogada: %d\tJogado por: %c\nTabela global:\n", p->numItem, p->player);

            mostraMat(p->bigScreen, S, S);
            printf("Tabela %d:\n", p->numTab);
            mostraMat(p->screen, N, N);
            p = p->prox;
            
            if(p != NULL)
                printf("\t---------//..........\n");
        }
    }else
        printf("Historioco de jogadas vazio...\n");

    printf("-------------Fim da Lista--------------\n\n");
}

int checkWin(char **p, int nLin, int nCol){
    int i, j;

    // Verifia as linhas
    for(i=0; i<nLin; i++)
        if(p[i][0] != '_')
            for(j=0; j<nCol-1 && p[i][j] == p[i][j+1]; j++);
                if(j==nCol-1)
                    return 1;


    // Verifia as colunas
    for(i=0; i<nCol; i++)
        if(p[0][i] != '_')
            for(j=0; j<nLin-1 && p[j][i] == p[j+1][i]; j++);
                if(j==nLin-1)
                    return 1;


    // Bloco de verificação as diagonais
    if(p[0][0] != '_')
        for(i=0; i<nLin-1 && p[i][i] == p[i+1][i+1]; i++); // Esquerda para a direita de cima para baxio
            if(i==nLin-1)
                return 1;

    
    if(p[nLin-1][0] != '_')
        for(i=0; i<nCol-1 && p[nLin-1-i][i] == p[nLin-2-i][i+1]; i++); // Esquerda para a direita de baico para cima
            if(i==nCol-1)
                return 1;

    return 0;
}

void coorTrans(int coor, int nLin, int *x, int *y){
    *x = 0;
    while(coor > nLin){
        coor -= nLin;
        (*x)++;
    }
    *y = coor - 1;
}

int nullListCheck(phisto p){
    if(p == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int startGame(int robotMode, int fileSave){
    int i, j;   //  Variaveis para ciclos
    int coor = 10, x, y;   //   Variaveis de coordenadas
    int jogadas = 0, jogador, fimDeJogo = 0, target, local;   //    Variaveis do jogo (int)
    char cmd, resposta;   //    Variavel de commando
    char point, peca, winner;   //  Variaveis de jogo (char)
    char tab[] = "Global";  //  Variavel de string 
    char **guideTab, **globalTab;   //  Matriz do Tabuleiro guia, Matriz do Tabuleiro global

    initRandom();   //  Iniciar um timer para o dar valores aleatórios para funções futuras
    phisto lista = NULL; // Iniciar a lista como vazia

    //  Escolhe qual jogador que começa
    jogador = intUniformRnd(0, 1);

    //  Criar tabela global
    globalTab = criaMat(S, S);

    if(globalTab == NULL){   //    Caso falha na criação da matriz
        printf("Erro - falha na criacao do Tabuleiro Global\n");
        return 0;
    }

    //  Criar os Mini Tabuleiros
    miniTab mT[mTLength];

    //  Preenchimento dos mini tabuleiros
    for (i = 0; i < 9 ; i++){
        mT[i].grid = criaMat(N, N);

        if(mT[i].grid == NULL){   //    Caso falha na criação da matriz
            printf("Erro - falha na criacao dos Mini Tabuleiros\n");
            return 0;
        }

        mT[i].numName = i + 1;
        mT[i].value = 95;   //  <=> mT[i].value = "_";
    }

    if(!nullListCheck){   //    Caso falha na criação da lista
        printf("Erro - lista de jogadas nao comecou vazia\n");
        return 0;
    }

    //  Criar a tabela guia
    guideTab = criaMat(N, N);
    if(guideTab == NULL){   //    Caso falha na criação da matriz
        printf("Erro - falha na criacao do Tabuleiro Global\n");
        //resetGame(globalTab, S, mT, N);
        return 0;
    }
    guideTab = prencMat(guideTab, N, N);

    if(fileSave){
        printf("Carregar save...\n");
        
        lista = loadFile(&jogadas, &local, &jogador, globalTab, S, mT, mTLength);

        printf("Carregameno completo!\n");
    }

    printf("Se quiseres a lista de comandos, escreva 'h' na parte de comandos para aparecer\n");

    //  Mostra tabuleiro global (Inicio de jogo) ou mostra o mini tabuleiro que tava a jogar no save
    if(!jogadas){
        printf("Tabela: %s\n", tab);
        mostraMat(globalTab, S, S);
    } else {
        printf("Tabela: %d\n", local + 1);
        mostraMat(mT[local].grid, N, N);
    }
    
    //  Inicia loop do jogo
    while (fimDeJogo != 1 && jogadas < (N * N * mTLength))
    {
        //  Bloco de seleção de personagem de jogada
        if(jogador == 0){
            peca = 79;   // <=> peca = "O";
            jogador = 1;
        }else{  //  Se for PvM, o robo fica com a peca "X"
            peca = 88;   // <=> peca = "X";
            jogador = 0;
        }

        //  Bloco de leitura e de verificação
        do
        {
            coor = mTLength + 1; // Reset de coor

            //  Bloco de leitura
            //  Caso o modo seja o PvM e é a ronda do robo, ele joga. Se não, é o jogador
            if(robotMode && !jogador){
                printf("Jogada: %d  || Jogador %c (Robo): ", jogadas, peca);
                cmd = intUniformRnd(1, 9) + '0';    //  Escolhe um número entre 1 e 9 e trasnforma em string para ser lido como comando
                printf("%c\n", cmd);
            } else {
                printf("Jogada: %d  || Jogador %c: ", jogadas, peca);
                scanf(" %c", &cmd);
                cmd = tolower(cmd); //  Transforma o cmd em lower case (ex: L → l)
                printf("\n");
            }

            //  Bloco de commandos de jogo
            switch (cmd)
            {
                //  Comando guide - mostrar o Tabuleiro guia
                case 'g': 
                    printf("Tabuleiro Guia: \n");
                    mostraMat(guideTab, N, N);
                    break;

                //  Comando tab - mostra o Tabuleiro global
                case 't':
                    printf("Tabuleiro Global: \n");
                    mostraMat(globalTab, S, S);
                    break;

                //  Comando local - mostra o Tabuleiro local
                case 'l':
                    if(!jogadas){
                        printf("Comando disponivel depois de colocar a primeira peca\n");
                    }else{
                        printf("Tabela: %d\n", local + 1);
                        mostraMat(mT[target].grid, N, N);
                    }
                    break;

                //  Comando all - mostra todos os tabuleiros (Tabuleiro global + Mini Tabuleiro)
                case 'a':
                    printf("Tabela: %s\n", tab);
                    mostraMat(globalTab, S, S);
                    for(i=0; i<mTLength; i++){
                        printf("Tabela: %d\n", i+1);
                        mostraMat(mT[i].grid, N, N);
                    }
                    break;

                //  Commando past- mostra a listra de jogadas feitas no jogo e suas tabelas
                case 'p':
                    showList(lista, jogadas, robotMode);
                    break;

                //  Comando exit - comando para sair do jogo e perguntar se jogadore(s) querem salvar o jogo
                case 'e':
                    fflush(stdin);

                    printf("Vai querer salvar o jogo e jogar mais tarde? (Y/N) ");
                    scanf("%c", &resposta);
                    resposta = toupper(resposta);
                    if(resposta == 'Y'){
                        saveFile(jogadas, local, jogador, globalTab, S, mT, mTLength, lista);
                        printf("Salvo\n");
                        return 0;
                    }
                    return 0;
                    break;

                //  Comando de ajuda - lista de comandos que os jogadores podem fazer
                case 'h':
                    printf("Tabela de comandos:\n"
                        "1 a 9 - Local de jogada de peca\n"
                        "g - Mostra guia de jogada\n"
                        "t - Mostra Tabuleiro Global\n"
                        "l - Mostra Mini Tabuleiro\n"
                        "p - Mostra a lista de jogadas feitas neste jogo\n"
                        "a - Mostra todas os Tabuleiros (Tabuleiro Global + Minis Tabuleiros)\n"
                        "e - Sair do jogo\n");
                    break;

                //  Bloco de funcionalidade de peça 
                case '1' ... '9':
                    coor = cmd - '0';   //  coor = cmd transformado de string para int

                    if(!coor){
                        printf("Coordenada invalido\n");
                        break;
                    }

                    target = coor - 1;   // Próxima Mini Tabela (num) <=> coor

                    //  Na primeira jogada, o jogador decide em que miniTabuleiro começar
                    if (jogadas == 0)
                    {
                        fflush(stdin); //   Limpa o input para não saltar este passo de uma vez só

                        printf("Tabela: %d\n", target + 1);
                        mostraMat(mT[target].grid, N, N);

                        local = target;   //    Passamos a estar no Mini Tabuleiro que escolhemos

                        if(robotMode && !jogador){
                            printf("Jogada: %d  || Jogador %c (Robo): ", jogadas, peca);
                            coor = intUniformRnd(1, 9);
                            printf("%d\n", coor);
                        } else {
                            printf("Jogada: %d  || Jogador %c: ", jogadas, peca);
                            scanf("%d", &coor);
                            printf("\n");
                        }

                        target = coor - 1;
                    }

                    coorTrans(coor, N, &x, &y);

                    //  Validade de jogada e posicionamento de peça
                    point = getPos(mT[local].grid, x, y);
                    if(point != '_'){
                        printf("Jogada invalida!!\n");
                        mostraMat(mT[local].grid, N, N);
                        coor = mTLength + 1;
                    }else{
                        coorTrans(coor, N, &x, &y);
                        setPos(mT[local].grid, x, y, peca);
                        jogadas++;
                        lista = addPlay(lista, jogadas, peca, globalTab, mT[local].numName, mT[local].grid);
                    }

                    break;

                //  Se entrada de comando inválida
                default:
                    printf("Comando nao existe\n");
                    break;
            }

            fflush(stdin);   // Limpa o input de commando

        } while(coor > mTLength);     

        //  Blocode de validação de vitoria
        if(mT[local].value == 95){   // <=> if(mT[local].value == "_");
            if(checkWin(mT[local].grid, N, N)){
                mT[local].value = peca;
                coorTrans(local + 1, N, &x, &y);
                setPos(globalTab, x, y, peca);
                printf("Jogador %c ganhou o Mini Tabbuleiro %d\n", peca, mT[local].numName);
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
    
    if(!winner || jogadas >= (N * N * mTLength)){
        printf("Jogo acabou empatado\n");
        //resetGame(globalTab, S, mT, N);

        saveDelet();

        return 1;
    } else {
        printf("Parabens, o jogador %c ganhou o jogo.\n", peca);
        mostraMat(globalTab, S, S);
        //resetGame(globalTab, S, mT, N);
        
        saveDelet();

        return 1;
    }
}