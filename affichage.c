#include "affichage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fichiers.h"

void affichage(oxy myOxy)
{
	if (exists(".verrouData")) return;

	FILE* filePtr;
	int res;

	if ((filePtr = fopen("Data.txt", "w")) != 0)
	{
		FILE* lock;
		if ((lock = fopen(".verrouData", "w")) != 0)
		{
			char data[50];
			char buffer[10];

			sprintf(buffer, "%i", myOxy.spo2); // convert
			strcpy(data, buffer); // append
			strcat(data, "\n"); // append new line

			sprintf(buffer, "%i", myOxy.pouls); // convert
			strcat(data, buffer); // append

			fprintf(filePtr, "%s", data);
			fclose(filePtr);
			fclose(lock);

			remove(".verrouData");
		}
	}
	else
	{
		printf("Could not open interface file");
	}
}