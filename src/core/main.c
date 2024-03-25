#include <stdio.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

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
        toggleMainMenu();
        selectMenu();
    }
    return 0;
}