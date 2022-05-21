// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef MATDIN_H
#define MATDIN_H

// Liberta uma matriz dinâmica de caracteres com nLin linhas
void libertaMat(char** p, int nLin);

// Cria uma matriz dinâmica de caracteres  com nLin linhas e nCol colunas
// Devolve endereço inicial da matriz
char** criaMat(int nLin, int nCol);

// Imprime o conteúdo de uma matriz dinâmica de caracteres
void mostraMat(char **p, int nLin, int nCol);

// Coloca o caracter c na posição (x, y) de uma matriz dinâmica de caracteres
void setPos(char **p, int x, int y, char c);

// Obtém o caracter armazenado na posição (x, y) de uma matriz de caracteres
// Devolve o elemento nessa posição
char getPos(char **p, int x, int y);

// Preenche a matriz da esquerda para a direta, de cima para baixo, de 1 até ao número máximo de elementos da matriz
// Devolve endereço inicial da matriz
char** prencMat(char **p, int nLin, int nCol);

// Faz uma cópia da matriz
// Devolve endereço inicial da matriz
char** copyMat(char **p, int nLin, int nCol);

#endif /* MATDIN_H */