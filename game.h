// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef GAME_H
#define GAME_H

// Função de verificação de vitória no tabuleiro
// Devolve 1 caso seja verdade, 0 caso seja falso
int checkWin(char **p, int nLin, int nCol);

// Função que transfomra o numero de 1 a 9 em sua correspondente coordenadas do tabuleiro
void coorTrans(int coor, int nLin, int *x, int *y);

#endif /* GAME_H */