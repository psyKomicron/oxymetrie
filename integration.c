#include "integration.h"
#include <assert.h>
#include "fir.h"
#include "fichiers.h"
#include "mesure.h"
#include "iir.h"
#include "affichage.h"
#include "lecture.h"

void integrationTest(char* str)
{
	// TODO
	if (exists(str))
	{
        FILE* filePoint = fopen(str, "r");

		integration(filePoint);

		fclose(filePoint);
	}
    else
    {
        exit(2); // file does not exists
    }
}

void integration(FILE* filePoint)
{
    assert(filePoint);

    oxy mesureOxy = { 0, 0 };
    oldiir* oldIIR = initIir();

    int ret = 0;
    absorp abs;

    while (ret != EOF)
    {
        abs = lecture(filePoint, &ret);
        if (ret == ERR_FILE_CORRUPTED)
        {
            printf("%s\n", "File corrupted");
        }
        else if (ret == EOF)
        {
            printf("%s\n", "EOF");
        }
        else if (ret == ERR_SUCCESS)
        {
            printf("%f , %f , %f , %f\n", abs.acr, abs.dcr, abs.acir, abs.dcir);

            if (mesure(iir(fir(abs), oldIIR), &mesureOxy) == ERR_SUCCESS)
            {
                printf("%i , %i\n", mesureOxy.pouls, mesureOxy.spo2);
                affichage(mesureOxy);
            }
        }
        else
        {
            exit(-2);
        }
    }

    printf("%s", "Program ended !");
}