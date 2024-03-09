#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/card_service.h"

void addCard(char filename[])
{
    cardAddNSave(filename);
}

void queryCard(char filename[]){
    char a[20]={};
    printf("欲查询卡号：");
    scanf("%s", &a);
    
    cardQuery(a, filename);
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
