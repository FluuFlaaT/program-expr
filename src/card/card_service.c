#include <string.h>
#include "service.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif
#include "card_service.h"


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
    scanf("%f", &CARD->balance);

    if(CARD->balance < 0)
    {
        printf("金额非法！\n");
        CARD->Flag_Illegal = 1;
    }else{
        CARD->summary = CARD->balance;
        CARD->nStatus = 1;
        CARD->nDel = 0;
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

    Card->date.timestamp = (unsigned long)time(NULL);
}

// Check if exist. Exist = 1; Not exist = 0.
// ifOnline = 1 : if Offline return 1, if Online return 0
// ifOnline = 0 : DO NOT check status.
int checkIfExist(cardList Card, document * New, int ifPassword, int ifOnline)
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
                if(!ifPassword)
                {
                    return 1;
                }
                else
                {
                    if(!strcmp(tmp->password, New->password))
                    {
                        if(ifOnline)
                        {
                            if(tmp->nStatus == 0) return 1;
                            else return 0;
                        }
                        else return 1;
                    }
                    else return 0;
                }
            }
        }
        return 0;
    }
}

document * findExactCard(document * New)
{
    document * tmp = Card;
    if(tmp->cardNum == 0)
    {
        return NULL;
    }
    else
    {
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
            if(!strcmp(tmp->cardNumber, New->cardNumber) && !strcmp(tmp->password, New->password))
            {
                return tmp;
            }
        }
        return NULL;
    }
}