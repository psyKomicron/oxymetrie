#include "lecture.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

absorp lecture(FILE* filePoint, int* retState)
{
    assert(filePoint && retState);

    *retState = ERR_FILE_CORRUPTED;

    char frame[19] = { 0 };
    char c;
    bool notBreak = true;
    uint i = 0;


    bool valid = true;
    uint commas = 0, fieldsNumber = 0, fieldSize = 0;

    while ((c = fgetc(filePoint)) != EOF && notBreak)
    {
        if (c == '\n')
        {
            notBreak = false;
            if (commas != 3 && fieldsNumber != 3)
            {
                valid = false;
            }
            else
            {
                fieldsNumber++;
            }
        }
        else
        {
            // perform validity checks on the incoming frame
            if (c == ',')
            {
                commas++;
                if (fieldSize != 4)
                {
                    valid = false;
                }
                else
                {
                    fieldSize = 0;
                    fieldsNumber++;
                }
            }
            else if ((uint)c >= 30)
            {
                fieldSize++;
            }
            else
            {
                valid = false;
            }

            // if frame is validated -> put it in the return frame
            if (i < 19 && valid)
            {
                frame[i] = c;
            }
            else
            {
                notBreak = false;
            }
            i++;
        }
    }

    absorp myAbs = { 0, 0, 0, 0 };

    if (c == EOF && (fieldsNumber != 4 || commas != 3))
    {
        *retState = EOF;
        return myAbs;
    }

    if (valid)
    {
        *retState = ERR_SUCCESS;

        char fieldValue[4] = { 0 };
        float fields[4] = { 0 };
        uint forFrame = 0;
        for (i = 0; i < 4; i++)
        {
            size_t j = 0;
            while (j < 4 && frame[j] != ',')
            {
                fieldValue[j] = frame[forFrame];
                forFrame++;
                j++;
            }

            fields[i] = atof(fieldValue);
            forFrame++; // to skip ','
        }

        myAbs.acr = fields[0] - 2048;
        myAbs.dcr = fields[1];
        myAbs.acir = fields[2] - 2048;
        myAbs.dcir = fields[3];
    }
    else
    {
        notBreak = true;
        while ((c = fgetc(filePoint)) != EOL && c != EOF);
        //c = fgetc(filePoint);
    }

    return myAbs;
}
