#ifndef IIR_H

#include "define.h"
#define ALPHA 0.992

absorp iirTest(char* filename);


typedef struct { // structure conteant les anciennces valeurs de absorp
    float xacr;
    float yacr;
    float xacir;
    float yacir;
} oldiir;

absorp iir(absorp Abs, oldiir* Oldiir);
oldiir* initIir();

#endif // !IIR_H


