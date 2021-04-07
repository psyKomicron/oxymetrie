#include "fir.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "fichiers.h"

absorp buffer[51] = { 0 };
float FIR_TAPS[51] = {
    1.4774946e-019,
    1.6465231e-004,
    3.8503956e-004,
    7.0848037e-004,
    1.1840522e-003,
    1.8598621e-003,
    2.7802151e-003,
    3.9828263e-003,
    5.4962252e-003,
    7.3374938e-003,
    9.5104679e-003,
    1.2004510e-002,
    1.4793934e-002,
    1.7838135e-002,
    2.1082435e-002,
    2.4459630e-002,
    2.7892178e-002,
    3.1294938e-002,
    3.4578348e-002,
    3.7651889e-002,
    4.0427695e-002,
    4.2824111e-002,
    4.4769071e-002,
    4.6203098e-002,
    4.7081811e-002,
    4.7377805e-002,
    4.7081811e-002,
    4.6203098e-002,
    4.4769071e-002,
    4.2824111e-002,
    4.0427695e-002,
    3.7651889e-002,
    3.4578348e-002,
    3.1294938e-002,
    2.7892178e-002,
    2.4459630e-002,
    2.1082435e-002,
    1.7838135e-002,
    1.4793934e-002,
    1.2004510e-002,
    9.5104679e-003,
    7.3374938e-003,
    5.4962252e-003,
    3.9828263e-003,
    2.7802151e-003,
    1.8598621e-003,
    1.1840522e-003,
    7.0848037e-004,
    3.8503956e-004,
    1.6465231e-004,
    1.4774946e-019
};

absorp fir(absorp data)
{
	// shift
	for (size_t i = 51 - 1; i >= 1; i--)
	{
		buffer[i] = buffer[i - 1];
	}
	buffer[0] = data;
	

	float acr = 0., acir = 0.;
	for (size_t k = 0; k < 51; k++)
	{
		acr += FIR_TAPS[k] * buffer[k].acr;
		acir += FIR_TAPS[k] * buffer[k].acir;
	}
	data.acr = acr;
	data.acir = acir;

    return data;
}

absorp firTest(char* str)
{
	FILE* record1Dat = openFile("record1.dat");
	int res = 0;

    absorp input, lastValue = { 0, 0 };
	while (res != EOF)
	{
		input = readRecordFile(record1Dat, &res);
        if (res != EOF)
        {
            lastValue = fir(input);
        }
        printf("%f", lastValue.acir);
        printf("%c", ', ');
        printf("%f", lastValue.acr);
        printf("%c", '\n');
	}

	fclose(record1Dat);

	return lastValue;
}