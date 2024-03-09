#ifndef _DOCUMENT
#define _DOCUMENT
#include "service.h"
#endif

void addCardToFile(document New, char filename[]);

int checkIfExist(document New, char filename[]);

document queryInFile(char number[], char filename[]);