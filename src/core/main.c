#include <stdio.h>
#include "../include/menu.h"

char storageLocation[100] = "storage.txt";

int main()
{
    printf("hello\n");
    while(1)
    {
        toggleMainMenu();
        selectMenu(storageLocation);
    }
    return 0;
}