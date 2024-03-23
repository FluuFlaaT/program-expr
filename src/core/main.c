#include "../include/main.h"
#include <stdio.h>
#include "../include/menu.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _DOCUMENT
#define _DOCUMENT
#include "../include/global.h"
#endif

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