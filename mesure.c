#include "mesure.h"
#include <stdio.h>
#include <stdbool.h>

bool counting = false;
float last = 0;
uint zeros = 0;
uint counter = 0;
uint bpmAvg = 70;

bool crossedZero(float current)
{
	return (last > 0. && current < 0.) || (last < 0. && current > 0.);
}

oxy mesureTest(char* fileName)
{
}

int mesure(absorp input, oxy* mesure)
{
	if (crossedZero(input.acr))
	{
		if (counting && zeros == 4) // full length period
		{
			float bpm = 30000 / (counter / 2);
			//bpmAvg = (bpm + bpmAvg) / 2;
			mesure->pouls = bpm;

			counter = 0;
			counting = false;
			zeros = 0;

			return 0;
		}
		else
		{
			counting = true;
		}
		zeros++;
	}

	if (counting)
	{
		counter++;
	}

	last = input.acr;

	return -1;
}

float freq(absorp input)
{
	return 0.;
}
