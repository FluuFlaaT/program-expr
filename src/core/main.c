#include "../include/main.h"
#include <stdio.h>
#include "../include/menu.h"

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