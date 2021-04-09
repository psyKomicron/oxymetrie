#include "iir.h"
#include "fichiers.h"

absorp iirTest(char* str) {
    absorp    Abs;
    absorp result;
    int etat = 0;
    oldiir* Oldiir = initIir();
    FILE* file = fopen(str, "r");
    Abs = lireFichier(file, &etat);

    do {
        result = iir(Abs, Oldiir);
        Abs = lireFichier(file, &etat);
    } while (etat != EOF);

    finFichier(file);

    return result;
}

absorp iir(absorp Abs, oldiir* Oldiir) {
    //float alpha=0.992;
    float acr = Abs.acr;
    float acir = Abs.acir;

    absorp oldAbs = Abs;

    Abs.acr = Abs.acr - Oldiir->xacr + ALPHA * Oldiir->yacr;
    Oldiir->xacr = acr;
    Oldiir->yacr = Abs.acr;

    Abs.acir = Abs.acir - Oldiir->xacir + ALPHA * Oldiir->yacir;
    Oldiir->xacir = acir;
    Oldiir->yacir = Abs.acir;

    return Abs;
}

oldiir* initIir() {
    oldiir* ptriir = NULL;
    ptriir = malloc(sizeof(oldiir));
    if (ptriir)
    {
        ptriir->xacir = 0;
        ptriir->yacir = 0;
        ptriir->xacr = 0;
        ptriir->yacr = 0;
    }

    return ptriir;
}