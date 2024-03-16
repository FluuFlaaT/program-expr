#ifndef _GLOBAL
#define _GLOBAL
#include "../include/global.h"
#endif
#include <stdio.h>
void addCard(document[], int *);

void queryCard(document[], int);

void online();

void offline();

void charge();

void chargeBack();

void querySummary();

void deleteCard();

int checkIfExist(document[], char[], int);

void loadCardFromFile(document Card[], FILE * fp, int *);

void writeBackToFile(document Card[], char filename[], int * latest);