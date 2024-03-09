#include <stdio.h>
#include <string.h>
#include "../include/card_file.h"
#ifndef _DOCUMENT
#define _DOCUMENT
#include "../include/service.h"
#endif

int checkIfExist(document Check, char filename[])
{
    FILE * file = fopen(filename, "a+");

    document New;

    while(fscanf(file, "%s %s %d %d %d %d %d %d %d %d %d\n", &New.cardNumber, &New.password, &New.balance, &New.status, &New.summarySpent, &New.lastTimeUsed.Year, &New.lastTimeUsed.Month, &New.lastTimeUsed.Day, &New.lastTimeUsed.Hour, &New.lastTimeUsed.Minute, &New.lastTimeUsed.Second) == 11)
    {
        if(!strcmp(New.cardNumber, Check.cardNumber))
        {
            return 0;
        }
    }
    return 1;
}

void addCardToFile(document New, char filename[])
{
    FILE * file = fopen(filename, "a+");

    fprintf(file, "%s %s %d %d %d %d %d %d %d %d %d\n", New.cardNumber, New.password, New.balance, New.status, New.summarySpent, New.lastTimeUsed.Year, New.lastTimeUsed.Month, New.lastTimeUsed.Day, New.lastTimeUsed.Hour, New.lastTimeUsed.Minute, New.lastTimeUsed.Second);

    fclose(file);
}

document queryInFile(char number[], char filename[])
{
    FILE * file = fopen(filename, "r");

    document New;

    while(fscanf(file, "%s %s %d", &New.cardNumber, &New.password, &New.balance))
    {
        int flag = 0;
        for(int i = 0; i < strlen(New.cardNumber);i++)
        {
            if(New.cardNumber[i] != number[i]) flag++;
        }
        if(!flag) return New;
    }
    
}
