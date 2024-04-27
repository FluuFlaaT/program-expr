#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

void enterNumber(document *);

void enterPassword(document *);

void enterAmount(document *);

void updateOperation(document *);
void updateOperation_EXACT(Time *);

int checkIfExist(cardList Card, document * New, int ifPassword, int ifOnline);

document * findExactCard(document * New);