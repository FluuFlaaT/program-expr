#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include "../include/card_service.h"

#ifndef _GLOBAL
#define _GLOBAL
#include "../include/global.h"
#endif


void addCard(document Card[], int * latest)
{
    struct document New;
    New.Flag_Illegal = 0;
    New.usedTime = 0;
    New.summary = 0;
    enterNumber(&New);
    if(!New.Flag_Illegal)
    {
        Card[*latest] = New;
        *latest += 1;
        //printf("*latest = %d", *latest);
        printf("========= 添加的卡信息如下 =========\n");
        printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "密码", "状态", "金额");
        printf("%-10s\t%-10s\t%-10d\t%-10d\n", New.cardNumber, New.password, New.Flag_Illegal, New.balance);
    }
}
    

void queryCard(document Card[], int latest){
    char Input[100];
    printf("请输入该卡的卡号：");
    scanf("%s", Input);
    printf("\n");

    for(int i = 0; i < latest; i++)
    {
        if(!strcmp(Card[i].cardNumber, Input))
        {
            printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "卡号","状态","余额","累计使用","使用次数","上次使用时间");
            printf("%-10s\t%-10d\t%-10d\t%-10d\t%-10d\t%d-%d-%d %d:%d:%d\n", Card[i].cardNumber, Card[i].Flag_Illegal, Card[i].balance, Card[i].summary, Card[i].usedTime, Card[i].date.Year, Card[i].date.Month, Card[i].date.Day, Card[i].date.Hour, Card[i].date.Minute, Card[i].date.Second);
        }
    }
}

void online(){

}

void offline(){

}

void charge(){

}

void chargeBack(){

}

void querySummary(){

}

void deleteCard(){

}
