#include <stdlib.h>
#include <stdio.h>

#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

cardList Card;
cardList TAIL;

char CardFilename[100] = "data/card.txt";
char BillingFilename[100] = "data/billing.txt";
char ChargeFilename[100] = "data/charge.txt";
int debugFlag = 0;
BillingList BList;
BillingList BListTAIL;
float amountPerMinute = 0.5;
ChargeList ChargeSave;
ChargeList * ChargeSaveTAIL;
