#ifndef DEFINE_H
#define DEFINE_H

#define ERR_FILE_CORRUPTED		1
#define ERR_SUCCESS				0
#define EOL						0x0d

typedef struct
{
	float acr;
	float dcr;
	float acir;
	float dcir;
} absorp;

typedef	struct
{
	int spo2;
	int pouls;
} oxy;

typedef unsigned int uint;

#endif // !DEFINE_H


