#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing_service.h"

void loadBilling()
{
    FILE * fp = fopen(BillingFilename, "a+");

    BillingList tmp, tmpTAIL;
    tmp = malloc(sizeof(Billing));
    
    InitBilling(tmp);
    tmp->billingNum = 0;
    tmpTAIL = tmp;
    Billing * new = malloc(sizeof(Billing));

    if(fp == NULL)
    {
        printf("%s源文件不存在！\n", BillingFilename);
    }

    while(fscanf(fp, "%[^##]##%d##%d##%f##%d##%d\n", new->cardNumber, &new->tStart, &new->tEnd, &new->fAmount ,&new->nStatus, &new->nDel) == 6)
    {
        tmpTAIL->next = new;
        tmpTAIL = tmpTAIL->next;
        new = malloc(sizeof(Billing));
        tmp->billingNum++;
    }

    if(debugFlag)
    {
        printf("Load Billing Success. billingNum = %d\n", tmp->billingNum);
    }
    free(BList);
    BList = tmp;
    BListTAIL = tmpTAIL;
    fclose(fp);
}

void saveBilling()
{
    FILE * bill = fopen(BillingFilename, "w");

    BillingList here;
    here = BList->next;

    for(int i = 0; i < BList->billingNum; i++)
    {
        if (here != NULL && bill != NULL) {
            fprintf(bill, "%s##%ld##%ld##%f##%d##%d\n", here->cardNumber, here->tStart, here->tEnd, here->fAmount, here->nStatus, here->nDel);
            
        }
        here = here->next;
    }

    fclose(bill);
}