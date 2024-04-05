#include <stdio.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#pragma once
#include "card_file.h"

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
    initialCardHead(Card);
    TAIL = Card;
    while(1)
    {
        loadCard();
        toggleMainMenu();
        selectMenu();
    }
    return 0;
}