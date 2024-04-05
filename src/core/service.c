#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Card include
#include "card_service.h"
#include "card_file.h"

// Billing include
#include "billing_service.h"
#include "billing_file.h"

#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif


void addCard()
{
    struct document *New;
    New =  malloc(sizeof(document));
    enterNumber(New);
    if(checkIfExist(Card, New, 0, 0))
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
    else if(!checkIfExist(Card, New, 0, 0))
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
    document * cardToBeOnline;
    cardToBeOnline = malloc(sizeof(document));

    printf("========== 上机 ==========\n");
    printf("请输入上机卡号（长度为1~18）：");
    scanf("%s", cardToBeOnline->cardNumber);
    printf("请输入上机密码（长度为1~8）：");
    scanf("%s", cardToBeOnline->password);
    
    int flag = checkIfExist(Card, cardToBeOnline, 1, 0);
    int saveFlag = 0;
    if(debugFlag) printf("FLAG = %d\n", flag);
    
    printf("---------- 上机信息如下 ----------\n");
    
    if(flag)
    {
        cardToBeOnline = findExactCard(cardToBeOnline);
        if(cardToBeOnline->nStatus == 0)
        {
            saveFlag = 1;
        }
        else
        {
            if(cardToBeOnline->balance > 0)
            {
                cardToBeOnline->nStatus = 0;
                updateOperation(cardToBeOnline);
                if(debugFlag) printf("nStatus改变。更新日期。\n");
            }
            else
            {
                flag = 0;
            }
        }
    }

    if(flag == 0)
    {
        printf("上机失败！\n");
    }
    else
    {
        printf("上机成功！\n");
        printf("%-10s\t%-10s\t%-10s\n", "卡号", "余额" , "上次使用日期");
        printf("%-10s\t%-10.1f\t%d-%d-%d %02d:%02d:%02d\n", cardToBeOnline->cardNumber, cardToBeOnline->balance, cardToBeOnline->date.Year, cardToBeOnline->date.Month, cardToBeOnline->date.Day, cardToBeOnline->date.Hour, cardToBeOnline->date.Minute, cardToBeOnline->date.Second);
        if(saveFlag == 0)
        {
            BillingList tmp;
            tmp = malloc(sizeof(Billing));
            InitBilling(tmp);
            for(int i = 0; i < 20; i++)
            {
                tmp->cardNumber[i] = cardToBeOnline->cardNumber[i];
            }
            tmp->tStart = (unsigned long)time(NULL);
            BListTAIL->next = tmp;
            BListTAIL = BListTAIL->next;
            BList->billingNum++;
            if(debugFlag) printf("enter savebill function.\n");
            saveBilling();
        }
    }
    saveCard();
    free(cardToBeOnline);
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

void initialCardHead(cardList ca)
{
    ca->cardNum = 0;
    BList->billingNum = 0;
    BListTAIL = BList;
}