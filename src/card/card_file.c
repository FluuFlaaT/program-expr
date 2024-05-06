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
        // if(here->nDel == 0) fprintf(fp, "%s##%s##%f##%d##%f##%d##%d##%d##%d##%d##%d##%d##%d##%d##%d\n", here->cardNumber, here->password, here->balance, here->Flag_Illegal, here->summary, here->usedTime, here->date.Year, here->date.Month, here->date.Day, here->date.Hour, here->date.Minute, here->date.Second, here->date.timestamp, here->nDel, here->nStatus);
        // if(here->nDel == 0) fprintf(fp, "%s##%s##%f##%d##%f##%d##%d##%d##%d##%d##%d##%d##%d##%d##%d\n", here->cardNumber, here->password, here->balance, here->Flag_Illegal, here->summary, here->usedTime, here->date.Year, here->date.Month, here->date.Day, here->date.Hour, here->date.Minute, here->date.Second, here->date.timestamp, here->nDel, here->nStatus);
        // 卡号 密码 状态 开卡时间 截止时间 累计金额 最后使用时间 使用次数 当前余额 删除标识
        // "%d-%2d-%2d %2d:%2d##%lu"
        if(here->nDel == 0) fprintf(fp, "%s##%s##%d##%d-%02d-%02d %02d:%02d##%lu##%d-%02d-%02d %02d:%02d##%lu##%.2f##%d-%02d-%02d %02d:%02d##%lu##%d##%.2f##%d\n", here->cardNumber, here->password, here->nStatus, here->date_created.Year, here->date_created.Month, here->date_created.Day, here->date_created.Hour, here->date_created.Minute, here->date_created.timestamp, here->date_expired.Year, here->date_expired.Month, here->date_expired.Day, here->date_expired.Hour, here->date_expired.Minute, here->date_expired.timestamp, here->summary, here->date.Year, here->date.Month, here->date.Day, here->date.Hour, here->date.Minute, here->date.timestamp, here->usedTime, here->balance, here->nDel);
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
        // while(fscanf(fp, "%[^##]##%[^##]##%f##%d##%f##%d##%d##%d##%d##%d##%d##%d##%d##%d##%d\n", new->cardNumber, new->password, &new->balance, &new->Flag_Illegal, &new->summary, &new->usedTime, &new->date.Year, &new->date.Month, &new->date.Day, &new->date.Hour, &new->date.Minute, &new->date.Second, &new->date.timestamp, &new->nDel, &new->nStatus) == 15)
        while(
            // fscanf(fp, "%s##%s##%d##%d-%2d-%2d %2d:%2d##%lu##%d-%2d-%2d %2d:%2d##%lu##%f##%d-%2d-%2d %2d:%2d##%lu##%d##%f##%d\n", here->cardNumber, here->password, here->nStatus, here->date_created.Year, here->date_created.Month, here->date_created.Day, here->date_created.Hour, here->date_created.Minute, here->date_created.timestamp, here->date_expired.Year, here->date_expired.Month, here->date_expired.Day, here->date_expired.Hour, here->date_expired.Minute, here->date_expired.timestamp, here->summary, here->date.Year, here->date.Month, here->date.Day, here->date.Hour, here->date.Minute, here->date.timestamp, here->usedTime, here->balance, here->nDel);
                fscanf(fp, "%[^##]##%[^##]##%d##%d-%02d-%02d %02d:%02d##%lu##%d-%02d-%02d %02d:%02d##%lu##%f##%d-%02d-%02d %02d:%02d##%lu##%d##%f##%d\n", new->cardNumber, new->password, &new->nStatus, &new->date_created.Year, &new->date_created.Month, &new->date_created.Day, &new->date_created.Hour, &new->date_created.Minute, &new->date_created.timestamp, &new->date_expired.Year, &new->date_expired.Month, &new->date_expired.Day, &new->date_expired.Hour, &new->date_expired.Minute, &new->date_expired.timestamp, &new->summary, &new->date.Year, &new->date.Month, &new->date.Day, &new->date.Hour, &new->date.Minute, &new->date.timestamp, &new->usedTime, &new->balance, &new->nDel) == 25
        ){
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