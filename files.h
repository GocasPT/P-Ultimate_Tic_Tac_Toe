// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Guilherme de Sousa Camacho - 2021138502

#ifndef FILES_H
#define FILES_H

#include "game.h"

void saveFile(phisto lista, int total);

void loadFile(phisto lista, int *total);

int saveFileExists();

void saveDelet();

#endif /* FILES_H */