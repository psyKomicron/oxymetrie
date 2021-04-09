#ifndef FICHIERS_H
#define FICHIERS_H
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include <stdbool.h>


FILE* initFichier(char* nomFichier );
absorp lireFichier(FILE* pf, int* etat);
void finFichier(FILE* pf);

bool exists(char* fileName);
#endif

