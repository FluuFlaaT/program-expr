#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

void enterNumber(document *);

void enterPassword(document *);

void enterAmount(document *);

void updateOperation(document *);

int checkIfExist(cardList Card, document * New);