#include <stdlib.h>
#include <stdio.h>

#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

cardList Card;
cardList TAIL;

char CardFilename[100] = "card_save.txt";
char BillingFilename[100] = "billing_save.txt";
int debugFlag = 1;
BillingList BList;
BillingList BListTAIL;
