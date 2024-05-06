#ifndef _DOCUMENT
#define _DOCUMENT
#include "global.h"
#endif

void InitBilling(BillingList tmp);
Billing * findExactBilling(Billing *);
void saveChargeList();
void loadChargeList();