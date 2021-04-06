#include "affichage.h"
#include <stdio.h>
#include <string.h>

void affichage(oxy myOxy)
{
	// write in file to do shit
	while (isDataFileOpen());

	FILE* filePtr;
	errno_t res;

	if ((res = fopen_s(&filePtr, "Data.txt", "w")) != 0)
	{
		printf("Could not open interface file");
	}
	else
	{
		char data[50];
		char buffer[10];

		sprintf(buffer, "%i", myOxy.pouls); // convert
		strcpy(data, buffer); // append
		strcat(data, "\n"); // append new line

		sprintf_s(buffer, 10, "%i", myOxy.spo2); // convert
		strcat(data, buffer); // append

		fprintf(filePtr, "%s", data);
		fclose(filePtr);
	}
}

bool isDataFileOpen()
{
	return false;
}
