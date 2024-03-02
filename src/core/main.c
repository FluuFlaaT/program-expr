#include "main.h"
#include <stdio.h>
#include "menu.c"

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