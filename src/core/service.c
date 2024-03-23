#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include "../include/card_service.h"

int debugFlag = 1;

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
        Card->next = New;
        printf("========= 添加的卡信息如下 =========\n");
        printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "密码", "状态", "金额");
        printf("%-10s\t%-10s\t%-10d\t%-10d\n", New->cardNumber, New->password, New->Flag_Illegal, New->balance);
        TAIL = TAIL->next;
        if(debugFlag)
        {
            printf("========= TAIL: 添加的卡信息如下 =========\n");
            printf("%-10s\t%-10s\t%-10s\t%-10s\n", "卡号", "密码", "状态", "金额");
            printf("%-10s\t%-10s\t%-10d\t%-10d\n", TAIL->cardNumber, TAIL->password, TAIL->Flag_Illegal, TAIL->balance);
        }
    }
}

void queryCard(){

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