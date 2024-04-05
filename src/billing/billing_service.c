#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

void InitBilling(BillingList tmp)
{
    for(int i = 0; i < 20; i++)
    {
        tmp->cardNumber[i] = '\0';
    }
    tmp->tStart = 0;
    tmp->tEnd = 0;
    tmp->fAmount = 0;
    tmp->nStatus = 0;
    tmp->nDel = 0;
    tmp->tEnd = 0;
}