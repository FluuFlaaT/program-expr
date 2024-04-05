#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#pragma once
#include "card_service.h"
#include "card_file.h"

#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif


void addCard()
{
    struct document *New;
    New =  malloc(sizeof(document));
    enterNumber(New);
    if(checkIfExist(Card, New))
    {
        printf("卡号已存在！\n");
    }
    else if(!New->Flag_Illegal)
    {
        Card->cardNum++;
        TAIL->next = New;
        printf("========= 添加的卡信息如下 =========\n");
        printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "密码", "状态", "金额");
        printf("%-10s\t%-10s\t%-10d\t%.2f\n", New->cardNumber, New->password, New->Flag_Illegal, New->balance);
        TAIL = TAIL->next;
        saveCard();
        if(debugFlag)
        {
            printf("========= TAIL: 添加的卡信息如下 =========\n");
            printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "密码", "状态", "金额");
            printf("%-10s\t%-10s\t%-10d\t%.2f\n", TAIL->cardNumber, TAIL->password, TAIL->Flag_Illegal, TAIL->balance);
            printf("TimeStamp = %d\n", TAIL->date.timestamp);
        }
    }
}

void queryCard(){
    //char Input[100];
    document * New = malloc(sizeof(document));
    printf("请输入该卡的卡号：");
    scanf("%s", New->cardNumber);
    //printf("\n");
    if(strlen(New->cardNumber) > 18)
    {
        printf("卡片长度非法！\n");
    }
    else if(!checkIfExist(Card, New))
    {
        printf("卡号不存在！\n");
    }
    else
    {
        document * tmp = Card;
        for(int i = 0; i < Card->cardNum; i++)
        {
            tmp = tmp->next;
            if(!strcmp(tmp->cardNumber, New->cardNumber))
            {
                printf("%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n", "卡号","状态","余额","累计使用","使用次数","上次使用时间");
                printf("%-10s\t%-10d\t%-10.2f\t%-10.2f\t%-10d\t%d-%d-%d %02d:%02d:%02d\n", tmp->cardNumber, tmp->Flag_Illegal, tmp->balance, tmp->summary, tmp->usedTime, tmp->date.Year, tmp->date.Month, tmp->date.Day, tmp->date.Hour, tmp->date.Minute, tmp->date.Second);
                break;
            }
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

void initialCardHead(cardList Card)
{
    Card->cardNum = 0;
}