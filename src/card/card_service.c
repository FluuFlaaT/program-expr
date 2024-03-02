#include <string.h>
#include "service.h"
#include <stdlib.h>

document cardInfoRead()
{
    struct document New;
    printf("\n请输入卡号 <长度为1 ~ 18>： ");
    scanf("%s", New.cardNumber);

    printf("\n请输入密码 <长度为1 ~ 8>： ");
    scanf("%s", New.password);

    printf("\n请输入充值金额： ");
    scanf("%d", & New.balance);

    printf("\n创建成功！\n");
    return New;
}