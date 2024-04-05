#include <stdio.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <service.h>
#include "card_file.h"
#include "billing_file.h"


#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif



extern cardList Card;
extern cardList TAIL;
int main()
{
    printf("hello\n");
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