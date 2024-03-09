#include "../include/main.h"
#include <stdio.h>
#include "../include/menu.h"
#ifndef _GLOBAL
#define _GLOBAL
#include "../include/global.h"
#endif

int main()
{
    printf("hello\n");
    while(1)
    {
        toggleMainMenu();
        selectMenu();
    }
    return 0;
}