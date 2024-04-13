#include <time.h>
#define CARD_LENGTH 20

typedef struct Time
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;
    unsigned long timestamp;
}Time;

typedef struct document{
    char cardNumber[CARD_LENGTH];
    char password[10];
    float balance;
    Time date;
    int Flag_Illegal;
    float summary; // Summary of amount
    int usedTime;
    struct document * next;
    int cardNum;
    int nStatus; // 0 -> Offline; 1 -> Online
    int nDel; // 0 -> Exist ; 1 -> Deleted
}document, *cardList, *pointer;

typedef struct Billing
{
    char cardNumber[CARD_LENGTH];
    long int tStart;
    long int tEnd;
    float fAmount;
    int nStatus;
    int nDel;
    int billingNum;
    struct Billing * next;
}Billing, *BillingList;

typedef struct Charge
{
    char cardNumber[CARD_LENGTH];
    long int time;
    int nStatus;
    float amount;
    int nDel;
}Charge;

typedef struct ChargeList
{
    Charge data;
    struct ChargeList * next;
}ChargeList;

extern cardList Card;
extern cardList TAIL;
extern char CardFilename[];
extern char BillingFilename[];
extern int debugFlag;

extern BillingList BList;
extern BillingList BListTAIL;

extern float amountPerMinute;

extern ChargeList ChargeSave;