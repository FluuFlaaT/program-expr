#include "menu.h"
#include <math.h>
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
        updateOperation_EXACT(&New->date_created);
        updateOperation_EXACT(&New->date_expired);
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
            printf("TimeStamp = %lu\n", TAIL->date.timestamp);
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
                printf("%-10s\t%-10d\t%-10.2f\t%-10.2f\t%-10d\t%d-%d-%d %02d:%02d:%02d\n", tmp->cardNumber, tmp->nStatus, tmp->balance, tmp->summary, tmp->usedTime, tmp->date.Year, tmp->date.Month, tmp->date.Day, tmp->date.Hour, tmp->date.Minute, tmp->date.Second);
                //break;
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
        if(cardToBeOnline->nStatus == 1)
        {
            saveFlag = 1;
        }
        else
        {
            if(cardToBeOnline->balance > 0)
            {
                cardToBeOnline->nStatus = 1;
                updateOperation(cardToBeOnline);
                if(debugFlag) printf("nStatus改变。更新日期。\n");
            }
            else
            {
                flag = 0;
                if(debugFlag) printf("余额不足！ flag = 0\n");
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
            if(debugFlag) printf("Billing Num ++. Now Billing Num = %d\n", BList->billingNum);
            if(debugFlag) printf("enter savebill function.\n");
            saveBilling();
        }
    }
    saveCard();
    free(cardToBeOnline);
}

void offline(){
    // Require cardNumber and password
    document * cardToBeOffline = malloc(sizeof(document));
    printf("========== 下机 ==========\n");
    printf("请输入下机卡号（长度为1~18）：");
    scanf("%s", cardToBeOffline->cardNumber);
    printf("请输入下机密码（长度为1~8）：");
    scanf("%s", cardToBeOffline->password);
    long timestamp;
    float amount = 0;

    // Find card
    int flag = checkIfExist(Card, cardToBeOffline, 1, 0);
    if(flag)
    {
        cardToBeOffline = findExactCard(cardToBeOffline);
        if(cardToBeOffline->nStatus == 1) flag = 1;
        else flag = 0;
    }
    // if(flag && cardToBeOffline->nStatus == 1) flag = 1;
    // else flag = 0;
    printf("---------- 下机信息如下 ----------\n");

    // If found && nStatus == 0, start offline process
    if(flag)
    {
        // Export card
        cardToBeOffline = findExactCard(cardToBeOffline);

        // Calculate amount
        long int timenow = (long int)time(NULL);
        timestamp = cardToBeOffline->date.timestamp;
        amount = ((int)((timenow - cardToBeOffline->date.timestamp) / 60.0) + ((timenow - cardToBeOffline->date.timestamp) % 60 )? 1 : 0) * amountPerMinute;

        // If amount is enough to pay
        if(amount > cardToBeOffline->balance) flag = 0;
        else
        {
            cardToBeOffline->nStatus = 0;
            cardToBeOffline->balance -= amount;
            cardToBeOffline->usedTime++;
            updateOperation(cardToBeOffline);
            if(debugFlag) printf("nStatus = 1, Timestamp changed.\n");
        }
    }
    // Else, printf ERROR
    if(flag == 0) printf("下机失败！\n");
    else
    {
        Billing * toBeSavedBilling = malloc(sizeof(Billing));
        for(int i = 0; i < 20; i++)
        {
            toBeSavedBilling->cardNumber[i] = cardToBeOffline->cardNumber[i];
        }
        toBeSavedBilling = findExactBilling(toBeSavedBilling);
        printf("下机成功！\n");
        printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "余额", "消费" , "下机时间");
        printf("%-10s\t%-10.1f\t%-10.1f\t%d-%d-%d %02d:%02d:%02d\n", cardToBeOffline->cardNumber, cardToBeOffline->balance, amount , cardToBeOffline->date.Year, cardToBeOffline->date.Month, cardToBeOffline->date.Day, cardToBeOffline->date.Hour, cardToBeOffline->date.Minute, cardToBeOffline->date.Second);
        if(toBeSavedBilling == NULL) printf("记录不存在！\n");
        else
        {
            toBeSavedBilling->nStatus = 1;
        }
        saveBilling();
    }

    saveCard();
    // Free and write back
    free(cardToBeOffline);
}

void charge(){
    ChargeList * tmp = malloc(sizeof(ChargeList));

    document * cardToBeCharged = malloc(sizeof(document));
    float amount;
    printf("---------- 充值 ----------\n");
    printf("请输入卡号：");
    scanf("%s", cardToBeCharged->cardNumber);
    printf("请输入密码：");
    scanf("%s", cardToBeCharged->password);
    printf("请输入充值金额：");
    scanf("%f", &amount);
    int flag1 = checkIfExist(Card, cardToBeCharged, 1, 0);
    if(amount <= 0) flag1 = 0;
    // int flag2 = checkIfExist(Card, cardToBeCharged, 1, 1);

    // TODO: 前面的保存时判断卡片有没有被删除
    printf("---------- 充值结果如下 ----------\n");
    if(flag1)
    {
        cardToBeCharged = findExactCard(cardToBeCharged);
        (*cardToBeCharged).balance += amount;
        (*cardToBeCharged).summary += amount;
        printf("%-20s\t%-10s\t%-10s\n", "卡号", "充值金额", "余额");
        printf("%-20s\t%-10.2f\t%-10.2f\n", cardToBeCharged->cardNumber, amount, cardToBeCharged->balance);
        strcpy(tmp->data.cardNumber, cardToBeCharged->cardNumber);
        tmp->data.amount = amount;
        tmp->data.nStatus = 0;
        tmp->data.time = time(NULL);
        tmp->data.nDel = 0;
        ChargeSaveTAIL->next = tmp;
        ChargeSaveTAIL = ChargeSaveTAIL->next;
    }
    else
    {
        printf("充值失败！\n");
    }
    saveCard();
    saveChargeList();

    free(tmp);
    free(cardToBeCharged);
    
}

void chargeBack(){
    ChargeList * tmp = malloc(sizeof(ChargeList));

    document * cardToBeCharged = malloc(sizeof(document));
    float amount;
    printf("---------- 退费 ----------\n");
    printf("请输入卡号：");
    scanf("%s", cardToBeCharged->cardNumber);
    printf("请输入密码：");
    scanf("%s", cardToBeCharged->password);
    printf("请输入退费金额：");
    scanf("%f", &amount);
    // flag1：卡片是否存在
    int flag1 = checkIfExist(Card, cardToBeCharged, 1, 0);
    // flag2：卡片是否正在上机
    int flag2 = checkIfExist(Card, cardToBeCharged, 1, 1);
    if(amount <= 0) flag1 = 0;

    // TODO: 前面的保存时判断卡片有没有被删除
    printf("---------- 充值结果如下 ----------\n");
    if(flag1)
    {
        cardToBeCharged = findExactCard(cardToBeCharged);
        if(cardToBeCharged->balance >= amount)
        (*cardToBeCharged).balance -= amount;
        (*cardToBeCharged).summary += amount;
        printf("%-20s\t%-10s\t%-10s\n", "卡号", "退费金额", "余额");
        printf("%-20s\t%-10.2f\t%-10.2f\n", cardToBeCharged->cardNumber, amount, cardToBeCharged->balance);
        strcpy(tmp->data.cardNumber, cardToBeCharged->cardNumber);
        tmp->data.amount = amount;
        tmp->data.nStatus = 1;
        tmp->data.time = time(NULL);
        tmp->data.nDel = 0;
        ChargeSaveTAIL->next = tmp;
        ChargeSaveTAIL = ChargeSaveTAIL->next;
    }
    else
    {
        printf("退费失败！\n");
    }
    saveCard();
    saveChargeList();

    free(tmp);
    free(cardToBeCharged);
}

void querySummary(){

}

void deleteCard(){
    printf("---------- 注销卡片 ----------\n");
    
    document * tmp = malloc(sizeof(document));
    printf("请输入注销卡卡号：");
    scanf("%s", tmp->cardNumber);
    printf("请输入注销卡密码：");
    scanf("%s", tmp->password);

    int flag1 = checkIfExist(Card, tmp, 1, 0);
    int flag2 = checkIfExist(Card, tmp, 1, 1);

    printf("-------- 注销信息 --------\n");
    if(flag1 && flag2)
    {
        tmp = findExactCard(tmp);
        (*tmp).nDel = 1;
        printf("%-20s\t%-10s\n","卡号", "退款余额");
        printf("%-20s\t%-10.2f\n", tmp->cardNumber, tmp->balance);
    }
    else
    {
        printf("注销失败！\n");
    }

    saveCard();
    free(tmp);
}

void initialCardHead(cardList ca)
{
    ca->cardNum = 0;
    BList->billingNum = 0;
    BListTAIL = BList;
}