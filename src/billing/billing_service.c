#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

#include <string.h>

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

Billing * findExactBilling(Billing * New)
{
    Billing * tmp = BList;
    if(tmp->billingNum == 0)
    {
        return NULL;
    }
    else
    {
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
            if(!strcmp(tmp->cardNumber, New->cardNumber))
            {
                return tmp;
            }
        }
        return NULL;
    }
}