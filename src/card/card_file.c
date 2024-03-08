#include <stdio.h>
#include "../include/card_file.h"
#ifndef _DOCUMENT
#define _DOCUMENT
#include "../include/service.h"
#endif

void addCardToFile(document New, char filename[])
{
    FILE * file = fopen(filename, "a+");

    fprintf(file, "%s %s %d\n", New.cardNumber, New.password, New.balance);

    fclose(file);
}
