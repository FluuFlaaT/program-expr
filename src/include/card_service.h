#ifndef _DOCUMENT
#define _DOCUMENT
#include "service.h"
#endif

document cardInfoRead();

int cardStorage();

void cardAddNSave(char filename[]);

document * cardQuery(char number[], char filename[]);

void updateOperation(document *Card);