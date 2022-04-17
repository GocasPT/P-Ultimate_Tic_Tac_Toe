// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef GAME_H
#define GAME_H

// Função de verificação de vitória no tabuleiro
// Devolve 1 caso seja verdade, 0 caso seja falso
int checkWin(char **p, int nLin, int nCol);

void mostraGuia(char **p, int nLin, int nCol);

#endif /* GAME_H */