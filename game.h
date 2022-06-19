// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef GAME_H
#define GAME_H

typedef struct miniTabuleiro miniTab;   // miniTabuleiro <=> miniTab
typedef struct historicoJogadas histo, *phisto;   // listaJogadas <=> lista, plista → listaJogadas

struct miniTabuleiro   // Estrutura de Mini Tabuleiros
{
    char **grid;    // Matriz do Mini Tabuleiro
    int numName;    // Numero do Mini Tabuleiros (1 a 9)
    char value;   // Valor do Mini Tabuleiros para o Tabuleiro global (X ou O)
};

struct historicoJogadas   // Estrutura dos elementos para a lista de jogadas
{
    int numItem;    // Número da jogada <=> númeor do item
    char player;    // O nome do jogador que fez a jogada
    char **bigScreen;   // "Screenshot" ao Tabuleiro gloval
    int numTab;   // Indentificação do Mini tabuleiro
    char **screen;   // "Screenshot" ao Mini Tabuleiro
    phisto prox;    // Próximo elemento da lista
};

// Função que adiciona a jogada na lista (ponteiro da lista, número da jogada, peça, Tabuleiro global, númeor do Tabuleiro, Mini Tabuleiro)
phisto addPlay(phisto p, int num, char peca, char **tab, int numTab, char **miniTab);

// Função preenchimento de informação para o novo elemento da lista de jogadas (ponteiro da lista, número da jogada, peça, Tabuleiro global, númeor do Tabuleiro, Mini Tabuleiro)
void fillItem(phisto p, int n, char peca, char **tab, int nT, char **mT);

// Função que mostra a lista de jogadas
void showList(phisto p, int jogadas , int modo);

// Função de verificação de vitória no tabuleiro
// Devolve 1 caso seja verdade, 0 caso seja falso
int checkWin(char **p, int nLin, int nCol);

// Função que transfomra o numero de 1 a 9 em sua correspondente coordenadas do tabuleiro
void coorTrans(int coor, int nLin, int *x, int *y);

// Função que verifica se a lista está vazia
// Devolve 1 caso seja verdade, 0 caso seja falso
int nullListCheck(phisto p);

// Função que inicia o jogo
// Entradas: Modo Robo (PvM) e carregar save (1 = sim, 0 = não)
int startGame(int robotMode, int saveFile);

#endif /* GAME_H */