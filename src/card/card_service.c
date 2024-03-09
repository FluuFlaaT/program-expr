#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/card_file.h"

document cardInfoRead(document *New)
{
    printf("\n请输入卡号 <长度为1 ~ 18>： ");
    scanf("%s", New->cardNumber);

    printf("\n请输入密码 <长度为1 ~ 8>： ");
    scanf("%s", New->password);

    printf("\n请输入充值金额： ");
    scanf("%d", & New->balance);

}

void cardAddNSave(char filename[])
{
    document New;
    updateOperation(&New);
    cardInfoRead(&New);
    if(!checkIfExist(New, filename))
    {
        printf("该卡片已存在！\n");
    }else{
        printf("\n创建成功！\n");
        addCardToFile(New, filename);
    }
}

document * cardQuery(char number[], char filename[])
{
    document new = queryInFile(number, filename);

    printf("卡号：%s\n余额：%d\n", new.cardNumber, new.balance);

    return &new;
}

void updateOperation(document *Card)
{
    time_t now = time(0);
    struct tm now_t = *localtime(&now);

    Card->lastTimeUsed.Year = now_t.tm_year + 1900;
    Card->lastTimeUsed.Month = now_t.tm_mon + 1; 
    Card->lastTimeUsed.Day = now_t.tm_mday;
    Card->lastTimeUsed.Hour = now_t.tm_hour;
    Card->lastTimeUsed.Minute = now_t.tm_min;
    Card->lastTimeUsed.Second = now_t.tm_sec;

}