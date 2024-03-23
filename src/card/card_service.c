#include <string.h>
#include "../include/service.h"
#include <stdlib.h>
#include <time.h>
#ifndef _DOCUMENT
#define _DOCUMENT
#include "../include/global.h"
#endif


void enterNumber(document * CARD)
{
    printf("\n请输入卡号 <长度为1 ~ 18>： ");
    scanf("%s", CARD->cardNumber);

    if(strlen(CARD->cardNumber) > 18)
    {
        printf("卡号非法！\n");
        CARD->Flag_Illegal = 1;
    }
    else
    {
        enterPassword(CARD);
    }
}

void enterPassword(document * CARD)
{
    printf("请输入密码 <长度为1 ~ 8>： ");
    scanf("%s", CARD->password);

    if(strlen(CARD->password) > 8)
    {
        printf("密码非法！\n");
        CARD->Flag_Illegal = 1;
    }
    else
    {
        enterAmount(CARD);
    }
}

void enterAmount(document * CARD)
{
    printf("请输入金额： ");
    scanf("%d", &CARD->balance);

    if(CARD->balance < 0)
    {
        printf("金额非法！\n");
        CARD->Flag_Illegal = 1;
    }else{
        CARD->summary += CARD->balance;
        updateOperation(CARD);
    }
}

void updateOperation(document *Card)
{
    time_t now = time(0);
    struct tm now_t = *localtime(&now);

    Card->date.Year = now_t.tm_year + 1900;
    Card->date.Month = now_t.tm_mon + 1; 
    Card->date.Day = now_t.tm_mday;
    Card->date.Hour = now_t.tm_hour;
    Card->date.Minute = now_t.tm_min;
    Card->date.Second = now_t.tm_sec;

}

int checkIfExist(cardList Card, document * New)
{
    document * tmp = Card;
    if(tmp->cardNum == 0)
    {
        return 0;
    }
    else
    {
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
            if(!strcmp(tmp->cardNumber, New->cardNumber))
            {
                return 1;
            }
        }
        return 0;
    }
}