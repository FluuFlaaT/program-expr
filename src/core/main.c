#include <stdio.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <service.h>
#include "card_file.h"
#include "billing_file.h"
#include <string.h>

#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif



extern cardList Card;
extern cardList TAIL;
int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        if(!strcmp(argv[1], "1")) debugFlag = 1;
    }
    if(debugFlag) printf("WARNING: debugFlag ENABLED\n");
    Card = malloc(sizeof(document));
    BList = malloc(sizeof(Billing));
    initialCardHead(Card);
    TAIL = Card;
    while(1)
    {
        loadCard();
        loadBilling();
        toggleMainMenu();
        selectMenu();
    }
    return 0;
}