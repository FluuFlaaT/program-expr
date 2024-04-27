#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/types/FILE.h>

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

void saveChargeList()
{
    FILE * fp = fopen(ChargeFilename, "w");
    ChargeList * tmp = ChargeSave.next;

    while(tmp != ChargeSaveTAIL->next)
    {
        fprintf(fp, "%s##%ld##%d##%f##%d\n", tmp->data.cardNumber, tmp->data.time, tmp->data.nStatus, tmp->data.amount, tmp->data.nDel);
        tmp = tmp->next;
    }
    fclose(fp);
}

void loadChargeList()
{
    FILE * fp = fopen(ChargeFilename, "a+");
    // ChargeList * tmp = malloc(sizeof(ChargeList) * 2);
    // ChargeList * tmpTAIL = tmp;
    // Charge * new = malloc(sizeof(Charge));

    /*
    ChargeList tmp;
    tmp.next = NULL;
    ChargeList * tmpTAIL = tmp.next;

    Charge *new;
    new = malloc(sizeof(Charge));

    if(fp == NULL)
    {
        printf("charge_save.txt源文件不存在！\n");
    }

    while(fscanf(fp, "%[^##]##%ld##%d##%f##%d\n", new->cardNumber, &new->time, &new->nStatus, &new->amount, &new->nDel) == 5)
    {
        tmpTAIL = malloc(sizeof(ChargeList));
        tmpTAIL->data = * new;
        tmpTAIL = tmpTAIL->next;
        new = malloc(sizeof(Charge));
    }
    ChargeSave = tmp;
    while(ChargeSaveTAIL != NULL && ChargeSaveTAIL->next != NULL)
    {
        ChargeSaveTAIL = ChargeSaveTAIL->next;
    }
    */

    ChargeList tmp;
    tmp.next = NULL;
    int count = 0;

    if(fp != NULL)
    {
        // tmp.next = malloc(sizeof(ChargeList));
        ChargeList * tmpTAIL = &tmp;
        // tmpTAIL = tmpTAIL->next;
        Charge * new;
        new = malloc(sizeof(Charge));
        while(fscanf(fp, "%[^##]##%ld##%d##%f##%d\n", new->cardNumber, &new->time, &new->nStatus, &new->amount, &new->nDel) == 5)
        {
            if(tmpTAIL->next == NULL)
            {
                tmpTAIL->next = malloc(sizeof(ChargeList));
                tmpTAIL->next->data = *new;
                ChargeSaveTAIL = tmpTAIL->next;
                tmpTAIL = tmpTAIL->next;
            }
            new = malloc(sizeof(Charge));
            count ++;
        }
    }

    ChargeSave = tmp;
    if(debugFlag) printf("Load Charge Finished. i == %d \n", count);

    fclose(fp);
}