#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include "service.c"

void toggleMainMenu()
{
    printf("欢迎使用网吧计费系统\n物联网2201 0122218390715 柏元丁\n");

    printf("---------- 菜单 ----------\n");
    printf("1.添加卡\n");
    printf("2.查询卡\n");
    printf("3.上机\n");
    printf("4.下机\n");
    printf("5.充值\n");
    printf("6.退费\n");
    printf("7.查询统计\n");
    printf("8.注销卡\n");
    printf("0.退出\n");

    printf("请选择菜单项编号（0 ～ 8）：");
}

void selectMenu()
{
    char * selection;
    selection = malloc(sizeof(char) * 100);
    scanf("%s", selection);
    if(!strcmp("1", selection)) addCard();
    else if(!strcmp("2", selection)) queryCard();
    else if(!strcmp("3", selection)) online();
    else if(!strcmp("4", selection)) offline();
    else if(!strcmp(selection , "5")) charge();
    else if(!strcmp(selection, "6")) chargeBack();
    else if(!strcmp(selection, "7")) querySummary();
    else if(!strcmp(selection, "8")) deleteCard();
    else if(!strcmp(selection, "0")) exit(0);
    else 
    {
        printf("输入的菜单序号有误！\n\n");
    }
    free(selection);
}