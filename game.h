// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef GAME_H
#define GAME_H

typedef struct miniTabuleiro miniTab;   // miniTabuleiro <=> miniTab
typedef struct listaJogadas lista, *plista;   // listaJOgadas <=> lista, plista → listaJOgadas

struct  miniTabuleiro;   // Estrutura de Mini Tabuleiros
struct listaJogadas;   // Estrutura dos elementos para a lista de jogadas

// Função que adiciona a jogada na lista (ponteiro da lista, número da jogada, peça, Tabuleiro global, númeor do Tabuleiro, Mini Tabuleiro)
plista addPlay(plista p, int num, char peca, char **tab, int numTab, char **miniTab);

// Função preenchimento de informação para o novo elemento da lista de jogadas (ponteiro da lista, número da jogada, peça, Tabuleiro global, númeor do Tabuleiro, Mini Tabuleiro)
void fillItem(plista p, int n, char peca, char **tab, int nT, char **mT);

// Função que mostra a lista de jogadas
void showList(plista p, int modo);

// Função de verificação de vitória no tabuleiro
// Devolve 1 caso seja verdade, 0 caso seja falso
int checkWin(char **p, int nLin, int nCol);

// Função que transfomra o numero de 1 a 9 em sua correspondente coordenadas do tabuleiro
void coorTrans(int coor, int nLin, int *x, int *y);

// Função que dá reset à memória no fim do jogo
void resetGame(char** tab, int nLinTab, miniTab* mTab, int nLinMtab);

// Função que verifica se a lista está vazia
// Devolve 1 caso seja verdade, 0 caso seja falso
int nullListCheck(plista p);

// Função que inicia o jogo
// Entradas: Modo Robo (PvM) e carregar save
int startGame(int robotMode, int saveFile);

#endif /* GAME_H */