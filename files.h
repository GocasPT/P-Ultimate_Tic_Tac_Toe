// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef FILES_H
#define FILES_H

#include "game.h"

//  Função que abre o bicheiro .bin para salvar o progresso do jogo
void saveFile(int jogadas, int state, int player, char** globalTab, int globalTabSize, miniTab* mT, int mTLenght, phisto lista);

//  Função que abre o bicheiro .bin para carrgar o progresso do jogo
//  Devolver a lista de jogadas feitas
phisto loadFile(int* jogadas, int* state, int* player, char** globalTab, int globalTabSize, miniTab* mT, int mTLenght);

//  Função que verifica se existe o ficheiro .bin de um jogo salvo antigo
// Devolve 1 se existe, 0 se não
int saveFileExists();

//  Função que apaga o ficheiro .bin de um jogo salvo antigo
void saveDelet();

#endif /* FILES_H */