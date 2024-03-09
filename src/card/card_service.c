#include <string.h>
#include "../include/service.h"
#include <stdlib.h>
#ifndef _GLOBAL
#define _GLOBAL
#include "../include/global.h"
#endif
#include "time.h"

document cardInfoRead()
{
    struct document New;
    printf("\n请输入卡号 <长度为1 ~ 18>： ");
    scanf("%s", New.cardNumber);

    printf("\n请输入密码 <长度为1 ~ 8>： ");
    scanf("%s", New.password);

    printf("\n请输入充值金额： ");
    scanf("%d", & New.balance);

    return New;
}

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