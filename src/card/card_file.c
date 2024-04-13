#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void saveCard()
{
    document* here;
    here = Card->next;
    FILE * fp = fopen(CardFilename, "w");

    for(int i = 0; i < Card->cardNum; i++)
    {
        if(here->nDel == 0) fprintf(fp, "%s##%s##%f##%d##%f##%d##%d##%d##%d##%d##%d##%d##%d##%d##%d\n", here->cardNumber, here->password, here->balance, here->Flag_Illegal, here->summary, here->usedTime, here->date.Year, here->date.Month, here->date.Day, here->date.Hour, here->date.Minute, here->date.Second, here->date.timestamp, here->nDel, here->nStatus);
        here = here->next;
    }

    fclose(fp);
}

void loadCard()
{
    FILE * fp = fopen(CardFilename, "a+");
    if(fp == NULL)
    {
        printf("本地卡信息不存在！\n");
    }
    else
    {
        document * new = malloc(sizeof(document));
        cardList newCardList;
        newCardList = malloc(sizeof(document));
        newCardList->cardNum = 0;
        document* here = newCardList;
        int i = 0;
        while(fscanf(fp, "%[^##]##%[^##]##%f##%d##%f##%d##%d##%d##%d##%d##%d##%d##%d##%d##%d\n", new->cardNumber, new->password, &new->balance, &new->Flag_Illegal, &new->summary, &new->usedTime, &new->date.Year, &new->date.Month, &new->date.Day, &new->date.Hour, &new->date.Minute, &new->date.Second, &new->date.timestamp, &new->nDel, &new->nStatus) == 15)
        {
            here->next = new;
            here = here->next;
            new = malloc(sizeof(document));
            newCardList->cardNum++;
        }
        if(debugFlag)
        {
            printf("Load Card Finished. i == %d \n", newCardList->cardNum);
        }
        free(Card);
        Card = newCardList;
        TAIL = here;
    }
    fclose(fp);
}